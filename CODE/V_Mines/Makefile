# test_ecran : main_test.c dessin_fct.c options.h vector.c signed_distance_function.c utiles.c light.c scene.c 3d_obj/*.c ray_marching.c 
# 	gcc main_test.c dessin_fct.c vector.c utiles.c ray_marching.c signed_distance_function.c light.c scene.c 3d_obj/*.c -O3 -lm -lglfw -lGL -o test_ecran

CC = clang
OPTIONS = -O3 -ffast-math -g
ADD = -lglfw -lGL -pthread -lm

all : testSimpson testPlage test

vector.o : vector.c vector.h options.h
	$(CC) -c vector.c $(OPTIONS) -o vector.o

utiles.o : utiles.c utiles.h options.h
	$(CC) -c utiles.c $(OPTIONS) -o utiles.o

signed_distance_function.o : signed_distance_function.c signed_distance_function.h vector.h utiles.h options.h bvh.h
	$(CC) -c signed_distance_function.c $(OPTIONS) -o signed_distance_function.o

scene.o : scene.h scene.c vector.h signed_distance_function.h utiles.h pingouin_sdf.h options.h bvh.h
	$(CC) -c scene.c $(OPTIONS) -o scene.o

bvh.o : bvh.h bvh.c vector.h signed_distance_function.h utiles.h pingouin_sdf.h options.h objets.h 
	$(CC) -c bvh.c $(OPTIONS) -o bvh.o

ray_marching.o : ray_marching.c ray_marching.h light.h vector.h options.h scene.h bvh.h objets.h
	$(CC) -c ray_marching.c $(OPTIONS) -o ray_marching.o

light.o : light.c light.h utiles.h vector.h scene.h options.h 
	$(CC) -c light.c $(OPTIONS) -o light.o

dessin_fct.o : dessin_fct.h dessin_fct.c options.h light.h
	$(CC) -c dessin_fct.c $(OPTIONS) -o dessin_fct.o

objets.o : objets.h objets.c vector.h signed_distance_function.h utiles.h pingouin_sdf.h options.h
	$(CC) -c objets.c $(OPTIONS) -o objets.o

simpson.o : simpsons_bvh.h simpsons_bvh.c options.h vector.h utiles.h signed_distance_function.h bvh.h objets.h
	$(CC) -c simpsons_bvh.c $(OPTIONS) -o simpson.o

plage.o : plage_bvh.h plage_bvh.c options.h vector.h utiles.h signed_distance_function.h bvh.h objets.h
	$(CC) -c plage_bvh.c $(OPTIONS) -o plage.o

pingouin.o : pingouin_sdf.h pingouin_sdf.c options.h vector.h utiles.h signed_distance_function.h bvh.h objets.h
	$(CC) -c pingouin_sdf.c $(OPTIONS) -o pingouin.o

# 3d obj
# 3d_obj/pingouin_1_sdf.o : 3d_obj/pingouin_1_sdf.h 3d_obj.pingouin_1_sdf.c vector.h utiles.h signed_distance_function.h
# 	$(CC) -c 3d_obj/pingouin_1_sdf.c -O3 -o 3d_obj/pingouin_1_sdf.o


# a enlever
# 3d_obj/pingouin_2_sdf.o : 3d_obj/pingouin_2_sdf.h 3d_obj/pingouin_2_sdf.c vector.h utiles.h signed_distance_function.h options.h
# 	$(CC) -c 3d_obj/pingouin_2_sdf.c -O3 -o 3d_obj/pingouin_2_sdf.o

# 3d_obj/cube_sdf.o : 3d_obj/cube_sdf.h 3d_obj/cube_sdf.c vector.h utiles.h signed_distance_function.h options.h
# 	$(CC) -c 3d_obj/cube_sdf.c -O3 -o 3d_obj/cube_sdf.o

#test_ecran : main_test.c options.h vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o 3d_obj/cube_sdf.o 3d_obj/pingouin_2_sdf.o
#	$(CC) main_test.c vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o 3d_obj/cube_sdf.o 3d_obj/pingouin_2_sdf.o -lm -lglfw -lGL -O3 -o test_ecran


testSimpson : main_simpson.c options.h vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o objets.o bvh.o simpson.o pingouin.o plage.o
	$(CC) main_simpson.c vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o objets.o bvh.o simpson.o pingouin.o plage.o $(OPTIONS) $(ADD) -o testSimpson

testPlage : main_plage.c options.h vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o objets.o bvh.o simpson.o pingouin.o plage.o
	$(CC) main_plage.c vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o objets.o bvh.o simpson.o pingouin.o plage.o $(OPTIONS) $(ADD) -o testPlage

test : TestsFree.c options.h vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o objets.o bvh.o simpson.o pingouin.o plage.o
	$(CC) TestsFree.c vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o objets.o bvh.o simpson.o pingouin.o plage.o $(OPTIONS) $(ADD) -o test


clean : 
	rm -f ./test_ecran
	rm -f *.o
	rm -f test testSimpson testPlage
# rm -f 3d_obj/*.o


