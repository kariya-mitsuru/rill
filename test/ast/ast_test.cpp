#define BOOST_TEST_MODULE ast_test
#include <boost/test/unit_test.hpp>

#include <memory>

#include <rill/ast.hpp>
#include <rill/ast/visitor.hpp>
//#include <rill/debug/debug.hpp>


#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>



BOOST_AUTO_TEST_SUITE( Ast )

BOOST_AUTO_TEST_CASE( empty_string )
{
    using namespace rill::ast;
    auto const stmt
        = std::make_shared<statements>(
            element::statement_list{
                std::make_shared<expression_statement>(
                    std::make_shared<binary_operator_expression>(
                        std::make_shared<term_expression>(
                            std::make_shared<intrinsic::int32_value>( 1 )
                            ),
                        make_binary_operator_identifier( "+" ),
                        std::make_shared<term_expression>(
                            std::make_shared<intrinsic::int32_value>( 2 )
                            )
                        )
                    )
            }
        );

    stmt->dump( std::cout );
}


class test_visitor_1
    : public rill::ast::ast_visitor<test_visitor_1, int>
{
public:
    using self_type = test_visitor_1;
    RILL_VISITOR_OP_DEFAULT
};

BOOST_AUTO_TEST_CASE( visitor_1 )
{
    using namespace rill::ast;
    auto const stmt
        = std::make_shared<statements>(
            element::statement_list{
                std::make_shared<expression_statement>(
                    std::make_shared<binary_operator_expression>(
                        std::make_shared<term_expression>(
                            std::make_shared<intrinsic::int32_value>( 1 )
                            ),
                        make_binary_operator_identifier( "+" ),
                        std::make_shared<term_expression>(
                            std::make_shared<intrinsic::int32_value>( 2 )
                            )
                        )
                    )
            }
        );

    test_visitor_1 v;
    v.dispatch( stmt );

    std::cout << "BO" << std::endl;
}

class test_visitor_1_c
    : public rill::ast::ast_visitor_const<test_visitor_1_c, int>
{
public:
    using self_type = test_visitor_1_c;
    RILL_VISITOR_OP_DEFAULT

public:
    test_visitor_1_c() {};
};

BOOST_AUTO_TEST_CASE( visitor_1_c )
{
    using namespace rill::ast;
    auto const stmt
        = std::make_shared<statements>(
            element::statement_list{
                std::make_shared<expression_statement>(
                    std::make_shared<binary_operator_expression>(
                        std::make_shared<term_expression>(
                            std::make_shared<intrinsic::int32_value>( 1 )
                            ),
                        make_binary_operator_identifier( "+" ),
                        std::make_shared<term_expression>(
                            std::make_shared<intrinsic::int32_value>( 2 )
                            )
                        )
                    )
            }
        );

    test_visitor_1_c const v;
    v.dispatch( stmt );

    std::cout << "BO" << std::endl;
}

class test_visitor_1_r
    : public rill::ast::readonly_ast_visitor<test_visitor_1_r, int>
{
public:
    using self_type = test_visitor_1_r;
    RILL_VISITOR_OP_DEFAULT
};

BOOST_AUTO_TEST_CASE( visitor_1_r )
{
    using namespace rill::ast;
    auto const stmt
        = std::make_shared<statements>(
            element::statement_list{
                std::make_shared<expression_statement>(
                    std::make_shared<binary_operator_expression>(
                        std::make_shared<term_expression>(
                            std::make_shared<intrinsic::int32_value>( 1 )
                            ),
                        make_binary_operator_identifier( "+" ),
                        std::make_shared<term_expression>(
                            std::make_shared<intrinsic::int32_value>( 2 )
                            )
                        )
                    )
            }
        );

    test_visitor_1_r v;
    v.dispatch( stmt );

    std::cout << "BO" << std::endl;
}


class test_visitor_1_rc
    : public rill::ast::readonly_ast_visitor_const<test_visitor_1_rc, int>
{
public:
    using self_type = test_visitor_1_rc;
    RILL_VISITOR_OP_DEFAULT

public:
    test_visitor_1_rc() {};
};

BOOST_AUTO_TEST_CASE( visitor_1_rc )
{
    using namespace rill::ast;
    auto const stmt
        = std::make_shared<statements>(
            element::statement_list{
                std::make_shared<expression_statement>(
                    std::make_shared<binary_operator_expression>(
                        std::make_shared<term_expression>(
                            std::make_shared<intrinsic::int32_value>( 1 )
                            ),
                        make_binary_operator_identifier( "+" ),
                        std::make_shared<term_expression>(
                            std::make_shared<intrinsic::int32_value>( 2 )
                            )
                        )
                    )
            }
        );

    test_visitor_1_rc const v;
    v.dispatch( stmt );

    std::cout << "BO" << std::endl;
}





BOOST_AUTO_TEST_SUITE_END()
