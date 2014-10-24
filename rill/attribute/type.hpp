//
// Copyright yutopp 2013 - .
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef RILL_ATTRIBUTE_TYPE_HPP
#define RILL_ATTRIBUTE_TYPE_HPP

#include <cstdint>

#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "attribute.hpp"


namespace rill
{
    namespace attribute
    {
        struct type_attributes_optional
        {
            boost::optional<attribute::holder_kind> quality;
            boost::optional<attribute::modifiability_kind> modifiability;
        };


        template<typename T>
        auto operator<<=( type_attributes& attr, T const& t )
            -> type_attributes&
        {
            detail::set( attr, t );
            return attr;
        }





        auto inline make_default_type_attributes()
            -> type_attributes
        {
            return { holder_kind::k_val, modifiability_kind::k_immutable };
        }

        auto inline make_empty_type_attributes()
            -> type_attributes
        {
            return { holder_kind::k_suggest, modifiability_kind::k_none };
        }

        template<typename... Args>
        auto inline make_type_attributes( Args const&... args )
            -> type_attributes
        {
            type_attributes attr = make_default_type_attributes();
            detail::set( attr, args... );
            return attr;
        }

        namespace detail
        {
            auto inline make_type_attributes_bit( type_attributes const& attr )
                -> attributes_bit_t
            {
                attributes_bit_t bits;

                std::cout << "Make_type_attributes_bit" << std::endl
                          << " q: " << attr.quality << std::endl
                          << " m: " << attr.modifiability << std::endl;

                bits.set( static_cast<std::size_t>( attr.quality ) );
                bits.set( static_cast<std::size_t>( attr.modifiability ) );

                return bits;
            }
        } // namespace detail




        enum class flatten_attribute
        {
            //
            from_val_immutable_to_val_immutable,
            from_val_immutable_to_val_const,
            from_val_immutable_to_val_mutable,
            from_val_immutable_to_ref_immutable,
            from_val_immutable_to_ref_const,
            from_val_immutable_to_ref_mutable,

            from_val_const_to_val_immutable,
            from_val_const_to_val_const,
            from_val_const_to_val_mutable,
            from_val_const_to_ref_immutable,
            from_val_const_to_ref_const,
            from_val_const_to_ref_mutable,

            from_val_mutable_to_val_immutable,
            from_val_mutable_to_val_const,
            from_val_mutable_to_val_mutable,
            from_val_mutable_to_ref_immutable,
            from_val_mutable_to_ref_const,
            from_val_mutable_to_ref_mutable,

            //
            from_ref_immutable_to_val_immutable,
            from_ref_immutable_to_val_const,
            from_ref_immutable_to_val_mutable,
            from_ref_immutable_to_ref_immutable,
            from_ref_immutable_to_ref_const,
            from_ref_immutable_to_ref_mutable,

            from_ref_const_to_val_immutable,
            from_ref_const_to_val_const,
            from_ref_const_to_val_mutable,
            from_ref_const_to_ref_immutable,
            from_ref_const_to_ref_const,
            from_ref_const_to_ref_mutable,

            from_ref_mutable_to_val_immutable,
            from_ref_mutable_to_val_const,
            from_ref_mutable_to_val_mutable,
            from_ref_mutable_to_ref_immutable,
            from_ref_mutable_to_ref_const,
            from_ref_mutable_to_ref_mutable,

            unknown
        };


        // This is hell
        template<typename Attributes>
        auto flat_attributes_conbination(
            Attributes const& source,
            Attributes const& target
            )
            -> flatten_attribute
        {
            switch( source.quality ) {
            case attribute::holder_kind::k_val:
                switch( source.modifiability ) {
                case attribute::modifiability_kind::k_immutable:
                    switch( target.quality ) {
                    case attribute::holder_kind::k_val:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_val_immutable_to_val_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_val_immutable_to_val_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_val_immutable_to_val_mutable;
                        } // switch( target_type.attributes.modifiability )

                    case attribute::holder_kind::k_ref:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_val_immutable_to_ref_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_val_immutable_to_ref_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_val_immutable_to_ref_mutable;
                        } // switch( target_type.attributes.modifiability )
                    } // switch( target_type.attributes.quality )


                case attribute::modifiability_kind::k_const:
                    switch( target.quality ) {
                    case attribute::holder_kind::k_val:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_val_const_to_val_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_val_const_to_val_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_val_const_to_val_mutable;
                        } // switch( target_type.attributes.modifiability )

                    case attribute::holder_kind::k_ref:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_val_const_to_ref_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_val_const_to_ref_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_val_const_to_ref_mutable;
                        } // switch( target_type.attributes.modifiability )
                    } // switch( target_type.attributes.quality )


                case attribute::modifiability_kind::k_mutable:
                    switch( target.quality ) {
                    case attribute::holder_kind::k_val:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_val_mutable_to_val_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_val_mutable_to_val_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_val_mutable_to_val_mutable;
                        } // switch( target_type.attributes.modifiability )

                    case attribute::holder_kind::k_ref:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_val_mutable_to_ref_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_val_mutable_to_ref_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_val_mutable_to_ref_mutable;
                        } // switch( target_type.attributes.modifiability )
                    } // switch( target_type.attributes.quality )
                } // switch( source_type.attributes.modifiability )


            case attribute::holder_kind::k_ref:
                switch( source.modifiability ) {

                case attribute::modifiability_kind::k_immutable:
                    switch( target.quality ) {
                    case attribute::holder_kind::k_val:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_ref_immutable_to_val_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_ref_immutable_to_val_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_ref_immutable_to_val_mutable;
                        } // switch( target_type.attributes.modifiability )

                    case attribute::holder_kind::k_ref:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_ref_immutable_to_ref_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_ref_immutable_to_ref_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_ref_immutable_to_ref_mutable;
                        } // switch( target_type.attributes.modifiability )
                    } // switch( target_type.attributes.quality )


                case attribute::modifiability_kind::k_const:
                    switch( target.quality ) {
                    case attribute::holder_kind::k_val:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_ref_const_to_val_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_ref_const_to_val_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_ref_const_to_val_mutable;
                        } // switch( target_type.attributes.modifiability )

                    case attribute::holder_kind::k_ref:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_ref_const_to_ref_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_ref_const_to_ref_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_ref_const_to_ref_mutable;
                        } // switch( target_type.attributes.modifiability )
                    } // switch( target_type.attributes.quality )


                case attribute::modifiability_kind::k_mutable:
                    switch( target.quality ) {
                    case attribute::holder_kind::k_val:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_ref_mutable_to_val_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_ref_mutable_to_val_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_ref_mutable_to_val_mutable;
                        } // switch( target_type.attributes.modifiability )

                    case attribute::holder_kind::k_ref:
                        switch( target.modifiability ) {
                        case attribute::modifiability_kind::k_immutable:
                            return flatten_attribute::from_ref_mutable_to_ref_immutable;
                        case attribute::modifiability_kind::k_const:
                            return flatten_attribute::from_ref_mutable_to_ref_const;
                        case attribute::modifiability_kind::k_mutable:
                            return flatten_attribute::from_ref_mutable_to_ref_mutable;
                        } // switch( target_type.attributes.modifiability )
                    } // switch( target_type.attributes.quality )



                } // switch( source_type.attributes.modifiability )
            } // switch( source_type.attributes.quality )


            assert( false && "[[ice]]" );
            return flatten_attribute::unknown;
        }










    } // namespace attributes
} // namespace rill


BOOST_FUSION_ADAPT_STRUCT(
    rill::attribute::type_attributes_optional,
    (boost::optional<rill::attribute::holder_kind>,        quality)
    (boost::optional<rill::attribute::modifiability_kind>,  modifiability)
    )


#endif /*RILL_ATTRIBUTE_TYPE_HPP*/
