filename = "pingouin_2"




with open(f"{filename}.txt",'r') as file:
    lines = file.readlines()

with open(f"{filename}_sdf.h","w") as file:
    file.write(f"#ifndef {filename.upper()+'_H'}\n")
    file.write(f"#define {filename.upper()+'_H'}\n\n")

    file.write('#include "../vector.h" \n')
    file.write('#include "../utiles.h" \n')
    file.write('#include "../signed_distance_function.h" \n\n')

    file.write(f"float SDF_{filename}(vector pts, vector c);\n")

    file.write("#endif")



with open(f"{filename}_sdf.c","w") as file:
    i = 1
    j = 0
    file.write(f'#include "{filename}_sdf.h"\n\n')

    file.write(f"float SDF_{filename}(vector pts, vector c) {{ \n")

    for l in lines:
        if l[0] == "v":
            coord = l.split(" ")
            coord[3] = coord[3].replace("\n","")
            file.write(f"   vector C_{i} = {{ {coord[1]},{coord[2]},{coord[3]} }};\n")
            i += 1

        if l[0] == "f":
            coord = l.split(" ")
            coord[3] = coord[3].replace("\n","")
            file.write(f"   float trig_{j} = SDF_triangle(pts,C_{coord[1]},C_{coord[2]},C_{coord[3]});\n")
            j += 1
    
    file.write(f"   int nb = {j};\n")
    file.write(f"   float all_sdf[{j}]; \n")
    for k in range(j):
        file.write(f"   all_sdf[{k}] = trig_{k}; \n")
    file.write(f"   return min_lst(all_sdf,{j});\n")
    file.write("}")
