//
// Copyright yutopp 2014 - .
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef RILL_SEMANTIC_ANALYSIS_ANALYZER_TYPE_DETAIL_FACTORY_HPP
#define RILL_SEMANTIC_ANALYSIS_ANALYZER_TYPE_DETAIL_FACTORY_HPP

#include <memory>

#include "../environment/environment_base.hpp"
#include "type_detail_pool_t.hpp"


namespace rill
{
    namespace semantic_analysis
    {
        class type_detail_factory
        {
        public:
            type_detail_factory(
                environment_base_ptr const& root_env,
                std::shared_ptr<type_detail_pool_t> const& pool
                )
                : root_env_( root_env )
                , pool_( pool )
            {}

        public:
            template<typename... Args>
            auto change_attributes( type_detail_ptr const& ty_d, Args&&... attrs )
                -> type_detail_ptr
            {
                auto ty = root_env_->get_type_at( ty_d->type_id );
                attribute::detail::set( ty.attributes, attrs... );

                auto new_type_id = root_env_->make_type_id( ty.class_env_id, ty.attributes );
                return pool_->construct(
                    new_type_id,
                    ty_d->target_env,
                    ty_d->nest,
                    ty_d->template_args
                    );
            }

        private:
            environment_base_ptr root_env_;

            std::shared_ptr<type_detail_pool_t> pool_;
        };

    } // namespace semantic_analysis
} // namespace rill

#endif /*RILL_SEMANTIC_ANALYSIS_ANALYZER_TYPE_DETAIL_FACTORY_HPP*/
