(*
 * Copyright yutopp 2015 - .
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *)

open Batteries
open Type_sets

include Sema_definitions
include Sema_context
include Sema_forward_ref
include Sema_construct_env

let make_default_env () =
  Env.make_root_env ()

let make_default_context root_env module_search_dirs =
  let open Sema_utils in
  let open Builtin_info in

  let type_gen = Type.Generator.default () in

  let type_type =
    register_builtin_type type_type_i.external_name
                          type_type_i.internal_name
                          type_type_i.mangled_name
                          Meta_level.OnlyMeta
                          (Some (Stdint.Uint32.of_int 8, Stdint.Uint32.of_int 8))
                          root_env type_gen
  in
  let void_type =
    register_builtin_type void_type_i.external_name
                          void_type_i.internal_name
                          void_type_i.mangled_name
                          Meta_level.Meta
                          None          (* TODO: fix *)
                          root_env type_gen
  in
  let tsets = Type_sets.make type_gen type_type void_type in

  let _ =
    register_builtin_lifetime "`static" (Lifetime.LtStatic) root_env;
    register_builtin_lifetime "`unmanaged" (Lifetime.LtUnmanaged) root_env;
    register_builtin_lifetime "`gc" (Lifetime.LtGc) root_env;
  in

  let uni_map = Unification.empty () in
  let ctfe_engine = Ctfe_engine.initialize tsets uni_map in
  let ctx = {
    sc_root_env = root_env;
    sc_builtin_m_env = None;

    sc_module_search_dirs = module_search_dirs;
    sc_module_bag = Module_info.Bag.empty ();

    sc_ctfe_engine = ctfe_engine;
    sc_tsets = tsets;
    sc_unification_ctx = uni_map;

    sc_handle_error = true;
    sc_errors = []
  } in

  ctx

let make_default_state system_libs_dirs user_srcs_dirs =
  let module_search_dirs = system_libs_dirs @ user_srcs_dirs in

  let env = make_default_env () in
  let ctx = make_default_context env module_search_dirs in
  (env, ctx)

let analyze_module mod_env ctx =
  assert (Env.is_incomplete mod_env);
  let mod_node = Option.get mod_env.Env.rel_node in
  let (node, _, _) = construct_env mod_node ctx.sc_root_env ctx None in
  match List.length ctx.sc_errors with
  | 0 -> Some node
  | _ -> None

let load_module filename env ctx =
  let timer = Debug.Timer.create () in
  Debug.reportf "= LOAD_MODULE(%s)" filename;
  let res =
    try
      let m = prepare_module_from_filepath filename ctx in
      analyze_module m ctx
      |> Option.map (fun sem_node ->
             Env.update_rel_ast m sem_node;
             Env.update_status m Env.Complete;
             m)
    with
    | Fatal_error err ->
       Sema_error.process_error err ctx;
       None
  in
  Debug.reportf "= LOAD_MODULE(%s) %s" filename (Debug.Timer.string_of_elapsed timer);
  res
