filename = "pingouin_2"




with open(f"{filename}.txt",'r') as file:
    lines = file.readlines()

with open(f"{filename}_sdf.h","w") as file:
    file.write(f"#ifndef {filename.upper()+'_H'}\n")
    file.write(f"#define {filename.upper()+'_H'}\n\n")

    file.write('#include "vector.h" \n')
    file.write('#include "utiles.h" \n')
    file.write('#include "sdf.h" \n\n')

    file.write(f"res_SDF scene_{filename}(vector pts);\n")

    file.write("#endif")



with open(f"{filename}_sdf.c","w") as file:
    i = 1
    j = 0
    file.write(f'#include "{filename}_sdf.h"\n\n')

    file.write(f"res_SDF scene_{filename}(vector pts) {{ \n")
    file.write(f"   int nb = ; \n")
    file.write(f"   res_SDF* all_sdf = malloc(nb*sizeof(res_SDF)); \n")

    for l in lines:
        if l[0] == "v":
            coord = l.split(" ")
            coord[3] = coord[3].replace("\n","")
            file.write(f"   vector C_{i} = {{ {coord[1]},{coord[2]},{coord[3]} }};\n")
            i += 1

        if l[0] == "f":
            coord = l.split(" ")
            coord[3] = coord[3].replace("\n","")
            file.write(f"   OBJET obj{j} = BuildTriangle(C_{coord[1]},C_{coord[2]},C_{coord[3]}, c_blanc);\n")
            j += 1
    
    for k in range (j):
        file.write(f"   FreeObj(obj{k});\n")
    
    file.write(f"res_SDF res = min_lst_sdf(all_sdf, nb);\n")

    file.write(f"   int nb = {j};\n")
    file.write(f"   free(all_sdf); \n")
    file.write(f"   return res;\n")
    file.write("}")
