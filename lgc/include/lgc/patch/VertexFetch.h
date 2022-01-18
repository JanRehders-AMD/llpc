/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2017-2022 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 **********************************************************************************************************************/
/**
 ***********************************************************************************************************************
 * @file  VertexFetch.h
 * @brief LLPC header file: contains declaration of class lgc::VertexFetch.
 ***********************************************************************************************************************
 */
#pragma once

#include "lgc/Pipeline.h"
#include "lgc/state/PipelineState.h"

namespace lgc {

class BuilderBase;

// =====================================================================================================================
// Public interface to vertex fetch manager.
class VertexFetch {
public:
  virtual ~VertexFetch() {}

  // Create a VertexFetch
  static VertexFetch *create(LgcContext *lgcContext);

  // Generate code to fetch a vertex value
  virtual llvm::Value *fetchVertex(llvm::Type *inputTy, const VertexInputDescription *description, unsigned location,
                                   unsigned compIdx, BuilderBase &builder) = 0;
};

// =====================================================================================================================
// Pass to lower vertex fetch calls
class LowerVertexFetch : public llvm::PassInfoMixin<LowerVertexFetch> {
public:
  llvm::PreservedAnalyses run(llvm::Module &module, llvm::ModuleAnalysisManager &analysisManager);

  bool runImpl(llvm::Module &module, PipelineState *pipelineState);

  static llvm::StringRef name() { return "Lower vertex fetch calls"; }
};

// =====================================================================================================================
// Pass to lower vertex fetch calls
class LegacyLowerVertexFetch : public llvm::ModulePass {
public:
  LegacyLowerVertexFetch();
  LegacyLowerVertexFetch(const LegacyLowerVertexFetch &) = delete;
  LegacyLowerVertexFetch &operator=(const LegacyLowerVertexFetch &) = delete;

  void getAnalysisUsage(llvm::AnalysisUsage &analysisUsage) const override {
    analysisUsage.addRequired<LegacyPipelineStateWrapper>();
  }

  virtual bool runOnModule(llvm::Module &module) override;

  static char ID; // ID of this pass
private:
  LowerVertexFetch m_impl;
};

} // namespace lgc
