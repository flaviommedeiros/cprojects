if (om->om_component != best_component
#if OPAL_ENABLE_FT_CR == 1
            && om->om_component != wrapper_component
#endif
            ) {
            /* Finalize */
                
            if (NULL != om->om_component->pmlm_finalize) {
                
                /* Blatently ignore the return code (what would we do to
                   recover, anyway?  This component is going away, so errors
                   don't matter anymore) */
                
                om->om_component->pmlm_finalize();
                opal_output_verbose(10, ompi_pml_base_framework.framework_output, 
                                    "select: component %s not selected / finalized",
                                    om->om_component->pmlm_version.mca_component_name);
            }
        }
