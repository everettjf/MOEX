//
// Created by everettjf on 2017/7/20.
//
#include "LoadCommand_DYSYMTAB.h"
#include "../MachHeader.h"

MOEX_NAMESPACE_BEGIN




std::tuple<bool, uint32_t, uint32_t> LoadCommand_LC_DYSYMTAB::GetDataRange()
{
    if(cmd_->tocoff>0)
        return std::make_tuple(true,cmd_->tocoff,cmd_->ntoc * sizeof(struct dylib_table_of_contents));
    if(cmd_->modtaboff>0){
        if(header_->Is64())
            return std::make_tuple(true,cmd_->modtaboff,cmd_->nmodtab * sizeof(struct dylib_module_64));
        else
            return std::make_tuple(true,cmd_->modtaboff,cmd_->nmodtab * sizeof(struct dylib_module));
    }
    if(cmd_->extrefsymoff>0)
        return std::make_tuple(true,cmd_->extrefsymoff,cmd_->nextrefsyms * sizeof(struct dylib_reference));
    if(cmd_->indirectsymoff>0)
        return std::make_tuple(true,cmd_->indirectsymoff,cmd_->nindirectsyms * sizeof(uint32_t));
    if(cmd_->extreloff>0)
        return std::make_tuple(true,cmd_->extreloff,cmd_->nextrel * sizeof(struct relocation_info));
    if(cmd_->locreloff>0)
        return std::make_tuple(true,cmd_->locreloff,cmd_->nlocrel * sizeof(struct relocation_info));
    return std::make_tuple(false,0,0);
}

std::vector<IndirectSymbolPtr> &LoadCommand_LC_DYSYMTAB::GetIndirectSymbols()
{
    if(indirect_symbols_.empty()){
        // todo
    }
    return indirect_symbols_;
}

MOEX_NAMESPACE_END

