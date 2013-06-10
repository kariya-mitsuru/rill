#pragma once

#include <memory>




// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
//
// statements
//
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
struct statement;
typedef std::shared_ptr<statement> statement_ptr;






template<typename Target>
struct template_statement;




class expression_statement;
typedef std::shared_ptr<expression_statement> expression_statement_ptr;





struct function_definition_statement_base;
typedef std::shared_ptr<function_definition_statement_base> function_definition_statement_base_ptr;






















struct native_function_definition_statement;
typedef std::shared_ptr<native_function_definition_statement> native_function_definition_statement_ptr;





struct class_definition_statement;
typedef std::shared_ptr<class_definition_statement> class_definition_statement_ptr;





typedef std::vector<statement_ptr>  program;

typedef std::vector<statement_ptr>  statement_list;