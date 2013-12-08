//
// Copyright yutopp 2013 - .
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef RILL_CODE_GENERATOR_LLVM_IR_GENERATOR_CONTEXT_HPP
#define RILL_CODE_GENERATOR_LLVM_IR_GENERATOR_CONTEXT_HPP

#include <memory>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

#include "llvm_ir_env_conversion_table.hpp"


namespace rill
{
    namespace code_generator
    {
        class llvm_ir_generator_context
        {
        public:
            llvm_ir_generator_context( std::string const& module_name = "rill" )
                : llvm_context( llvm::getGlobalContext() )
                , llvm_module( module_name, llvm_context )
                , ir_builder( llvm_context )
                {}
            
        public:
            llvm::LLVMContext& llvm_context;
            llvm::Module llvm_module;
            llvm::IRBuilder<> ir_builder;

            env_id_llvm_table env_conversion_table;
        };
        typedef std::shared_ptr<llvm_ir_generator_context> llvm_ir_generator_context_ptr;

    } // namespace code_generator
} // namespace rill

#endif /*RILL_CODE_GENERATOR_LLVM_IR_GENERATOR_CONTEXT_HPP*/