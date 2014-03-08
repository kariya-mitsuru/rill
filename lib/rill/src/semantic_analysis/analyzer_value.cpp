//
// Copyright yutopp 2013 - .
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <rill/semantic_analysis/semantic_analysis.hpp>
#include <rill/semantic_analysis/analyzer/identifier_solver.hpp>

#include <rill/environment/environment.hpp>

#include <rill/ast/statement.hpp>
#include <rill/ast/expression.hpp>
#include <rill/ast/value.hpp>


namespace rill
{
    namespace semantic_analysis
    {
        //
        //
        //
        RILL_TV_OP( analyzer, ast::nested_identifier_value, v, parent_env )
        {
            assert( false && "[[ICE]] not supported");
        }


        //
        //
        //
        RILL_TV_OP( analyzer, ast::identifier_value, v, parent_env )
        {
            return bind_type(
                v,
                solve_identifier( this, v, parent_env )
                );
        }



        //
        //
        //
        RILL_TV_OP( analyzer, ast::template_instance_value, v, parent_env )
        {
            return bind_type(
                v,
                solve_identifier( this, v, parent_env )
                );
        }



        //
        //
        //
        RILL_TV_OP( analyzer, ast::literal_value, v, env )
        {
            // look up literal type
            std::cout << v->literal_type_name_->get_inner_symbol()->to_native_string() << std::endl;

            // TODO: fix
            if ( v->literal_type_name_->get_inner_symbol()->to_native_string() == "array" ) {
                assert( false && "byaa" );
                
            } else {

                auto const class_env = root_env_->lookup( v->literal_type_name_ );
                assert( class_env != nullptr );  // literal type must exist

                //
                return bind_type(
                    v,
                    type_detail_pool_->construct(
                        class_env->make_type_id( class_env, determine_type_attributes() ),
                        class_env
                        )
                    );
            }
        }

    } // namespace semantic_analysis
} // namespace rill
