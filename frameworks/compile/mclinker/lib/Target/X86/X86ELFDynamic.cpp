//===- X86ELFDynamic.cpp --------------------------------------------------===//
//
//                     The MCLinker Project
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <mcld/LD/ELFFileFormat.h>
#include "X86ELFDynamic.h"

using namespace mcld;

X86ELFDynamic::X86ELFDynamic(const GNULDBackend& pParent)
  : ELFDynamic(pParent), m_HasGOTPLT(false) {
}

X86ELFDynamic::~X86ELFDynamic() {
}

void X86ELFDynamic::reserveTargetEntries(const ELFFileFormat& pFormat) {
  // reservePLTGOT
  if (m_HasGOTPLT ? pFormat.hasGOTPLT() : pFormat.hasGOT())
    reserveOne(llvm::ELF::DT_PLTGOT);
}

void X86ELFDynamic::applyTargetEntries(const ELFFileFormat& pFormat) {
  // applyPLTGOT
  if (m_HasGOTPLT) {
      if (pFormat.hasGOTPLT())
	applyOne(llvm::ELF::DT_PLTGOT, pFormat.getGOTPLT().addr());
  }
  else if (pFormat.hasGOT())
    applyOne(llvm::ELF::DT_PLTGOT, pFormat.getGOT().addr());
}
