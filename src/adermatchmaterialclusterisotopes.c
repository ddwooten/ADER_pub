/*****************************************************************************/
/*                                                                           */
/* serpent 2 (beta-version) : adermatchmaterialclusterisotopes.c             */
/*                                                                           */
/* Created:       2016/2/16 (DDW)                                            */
/* Last modified: 2019/06/09 (DDW)                                           */
/* Version:       2.1.31                                                     */
/*                                                                           */
/* Description: Loops through the isotopes of a given material to ensure that*/
/*              its cluster members have the same isotopes                   */
/*                                                                           */
/* Comments:This function is called from ADERCheckMaterialClusterIsotopes    */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/

#include "header.h"
#include "locations.h"

#define FUNCTION_NAME "ADERMatchMaterialClusterIsotopes:"

void ADERMatchMaterialClusterIsotopes(long mat)
{

    long iso = 0, found = 0, mat_ader_data = 0, mat_cluster_mem = 0, mat_cluster_mem_ent = 0;
    long mat_cluster_mem_iso = 0, mat_cluster_mem_nuc = 0, mat_cluster_mem_zai = 0;
    long nuc = 0, zai = 0;

    mat_ader_data = (long)RDB[mat + MATERIAL_ADER_DATA];

    mat_cluster_mem_ent = (long)RDB[mat_ader_data + ADER_MAT_CLUSTER_MEMS_PTR];

    while(mat_cluster_mem_ent > VALID_PTR)
    {

        /* Loop through all cluster members. Loop through all members isotopes */
        /* If an isotope is found to be missing from a cluster member, kill the program */

        mat_cluster_mem = (long)RDB[mat_cluster_mem_ent + ADER_MAT_CLUSTER_MEM_PTR];

        iso = (long)RDB[mat + MATERIAL_PTR_COMP];

        while(iso > VALID_PTR)
        {

            found = 0;

            nuc = (long)RDB[iso + COMPOSITION_PTR_NUCLIDE];

            zai = (long)RDB[nuc + NUCLIDE_ZAI];

            /* We must protect against a fictitious nuclide used in burnup routines */

            if(zai == -1)
            {

                iso = NextItem(iso);

                continue;

            }

            mat_cluster_mem_iso = (long)RDB[mat_cluster_mem + MATERIAL_PTR_COMP];

            while(mat_cluster_mem_iso > VALID_PTR)
            {

                mat_cluster_mem_nuc = (long)RDB[mat_cluster_mem_iso + COMPOSITION_PTR_NUCLIDE];

                mat_cluster_mem_zai = (long)RDB[mat_cluster_mem_nuc + NUCLIDE_ZAI];

                if(mat_cluster_mem_zai == zai)
                {

                    found = 1;

                    break;

                }

                mat_cluster_mem_iso = NextItem(mat_cluster_mem_iso);

            }

            if(found != 1)
            {

                Error(0, "An isotope in material, %s, \n\
with ZAI of %ld was not found, also, in material %s. \n\
ADER does not allow materials in the same cluster* to not have the same \n\
isotopes in their definitions. To add the isotope in question to \n\
material %s without affecting the original composition, simply add \n\
the missing isotope into the material's definition with zero fractional\n\
composition. \n \
*[A cluster is a group of materials which are linked together with ADER\n\
streams as defined by the 'stream' entries in the input files.\n\
The two materials listed above are members of the same cluster.]\n",
                      GetText(mat + MATERIAL_PTR_NAME),
                      zai, GetText(mat_cluster_mem + MATERIAL_PTR_NAME),
                      GetText(mat_cluster_mem + MATERIAL_PTR_NAME));

            }

            iso = NextItem(iso);

        }

        mat_cluster_mem_ent = NextItem(mat_cluster_mem_ent);

    }

}
