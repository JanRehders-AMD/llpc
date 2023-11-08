/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2020-2023 Advanced Micro Devices, Inc. All Rights Reserved.
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
 * @file  AbiUnlinked.h
 * @brief LLPC header file: contains declarations for "unlinked" ABI
 *
 * This file contains declarations for the ABI of an unlinked shader or part-pipeline ELF, generated by LGC
 * compilation and consumed by the LGC linker.
 ***********************************************************************************************************************
 */
#pragma once

#include "lgc/Builder.h"
#include "lgc/state/PipelineState.h"

namespace lgc {

// =====================================================================================================================
// Fetchless entry-point names. If the linker finds one of these names, it glues a fetch shader on to the front
// and changes the name to remove the "_fetchless" suffix.

// Name of shader entry-point for fetchless VS
static constexpr char FetchlessVsEntryName[] = "_amdgpu_vs_main_fetchless";
// Name of shader entry-point for merged ES-GS containing fetchless VS
static constexpr char FetchlessGsEntryName[] = "_amdgpu_gs_main_fetchless";
// Name of shader entry-point for ES that is fetchless VS
static constexpr char FetchlessEsEntryName[] = "_amdgpu_es_main_fetchless";
// Name of shader entry-point for merged LS-HS containing fetchless VS
static constexpr char FetchlessHsEntryName[] = "_amdgpu_hs_main_fetchless";
// Name of shader entry-point for LS that is fetchless VS
static constexpr char FetchlessLsEntryName[] = "_amdgpu_ls_main_fetchless";

// =====================================================================================================================
// Metadata names of extra entries in .pipeline for an unlinked shader/part-pipeline
namespace PipelineMetadataKey {

static const char VertexInputs[] = ".vertexInputs";
static const char ColorExports[] = ".colorExports";
static const char FragInputMapping1[] = ".fragInputs";
static const char FragInputMapping2[] = ".fragBuiltInInputs";
static const char FragInputMapping3[] = ".fragBuiltInInputInfo";
static const char DiscardState[] = ".discardState";

} // namespace PipelineMetadataKey

} // namespace lgc
