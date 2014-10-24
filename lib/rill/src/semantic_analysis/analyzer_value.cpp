//
// Copyright yutopp 2013 - .
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <rill/semantic_analysis/semantic_analysis.hpp>

#include <rill/environment/environment.hpp>

#include <rill/ast/ast.hpp>


namespace rill
{
    namespace semantic_analysis
    {
        //
        //
        //
        RILL_VISITOR_OP( analyzer, ast::nested_identifier_value, v, parent_env )
        {
            assert( false && "[[ICE]] not supported");
        }


        //
        //
        //
        RILL_VISITOR_OP( analyzer, ast::identifier_value, v, parent_env )
        {
            auto&& td = solve_identifier( v, parent_env );
            if ( td == nullptr ) {
                // compilation error...
                std::cout << "% name : " << v->get_inner_symbol()->to_native_string() << std::endl;
                assert( false && "[Error] identifier was not found." );
            }

            return bind_type( v, td );
        }



        //
        //
        //
        RILL_VISITOR_OP( analyzer, ast::template_instance_value, v, parent_env )
        {
            auto&& td = solve_identifier( v, parent_env );
            if ( td == nullptr ) {
                // compilation error...
                std::cout << "% name : " << v->get_inner_symbol()->to_native_string() << std::endl;
                assert( false && "[Error] identifier was not found." );
            }

            return bind_type( v, td );
        }


        RILL_VISITOR_OP( analyzer, ast::intrinsic::int32_value, v, parent_env )
        {
            auto const& class_env = get_primitive_class_env( v->get_native_typename_string() );
            assert( class_env != nullptr );  // literal type must exist

            //
            return bind_type(
                v,
                type_detail_pool_->construct(
                    class_env->make_type_id( class_env, attribute::make_default_type_attributes() ),
                    nullptr /*unused*/
                    )
                );
        }

        RILL_VISITOR_OP( analyzer, ast::intrinsic::boolean_value, v, parent_env )
        {
            auto const& class_env = get_primitive_class_env( v->get_native_typename_string() );
            assert( class_env != nullptr );  // literal type must exist

            //
            return bind_type(
                v,
                type_detail_pool_->construct(
                    class_env->make_type_id( class_env, attribute::make_default_type_attributes() ),
                    nullptr /*unused*/
                    )
                );
        }

        RILL_VISITOR_OP( analyzer, ast::intrinsic::string_value, v, parent_env )
        {
            auto const& class_env = get_primitive_class_env( v->get_native_typename_string() );
            assert( class_env != nullptr );  // literal type must exist

            //
            return bind_type(
                v,
                type_detail_pool_->construct(
                    class_env->make_type_id( class_env, attribute::make_default_type_attributes() ),
                    nullptr /*unused*/
                    )
                );
        }

        RILL_VISITOR_OP( analyzer, ast::intrinsic::array_value, v, parent_env )
        {
            auto const& ar
                = std::static_pointer_cast<ast::intrinsic::array_value>( v );

            // abyaaa
            ast::expression_list args = {
                ast::helper::make_id_expression(
                    ast::make_identifier( "int" )
                    ),
                std::make_shared<ast::term_expression>(
                    std::make_shared<ast::intrinsic::int32_value>(
                        ar->elements_list_.size()
                        )
                    )
            };

            auto const& i
                = ast::helper::make_id_expression(
                    std::make_shared<ast::term_expression>(
                        std::make_shared<ast::template_instance_value>(
                            "array",
                            args/*, true*/
                            )
                        )
                    );


            // solve array type...
            auto const& ty_d
                = resolve_type(
                    i,
                    attribute::holder_kind::k_val,
                    root_env_,
                    [&]( type_detail_ptr const& ty_d,
                         type const& ty,
                         class_symbol_environment_ptr const& class_env
                        ) {
                        assert( class_env->is_array() );

                        // connect fron LITARAL VALUE
                        class_env->connect_from_ast( v );
                    } );

            //
            return bind_type( v, ty_d );
        }

    } // namespace semantic_analysis
} // namespace rill
