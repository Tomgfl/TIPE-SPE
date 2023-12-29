# test_ecran : main_test.c dessin_fct.c options.h vector.c signed_distance_function.c utiles.c light.c scene.c 3d_obj/*.c ray_marching.c 
# 	gcc main_test.c dessin_fct.c vector.c utiles.c ray_marching.c signed_distance_function.c light.c scene.c 3d_obj/*.c -O3 -lm -lglfw -lGL -o test_ecran

CC = gcc

all : test_ecran

vector.o : vector.c vector.h options.h
	$(CC) -c vector.c -lm -O3 -o vector.o

utiles.o : utiles.c utiles.h
	$(CC) -c utiles.c -O3 -o utiles.o

signed_distance_function.o : signed_distance_function.c signed_distance_function.h vector.h utiles.h
	$(CC) -c signed_distance_function.c -lm -O3 -o signed_distance_function.o

scene.o : scene.h scene.c vector.h signed_distance_function.h utiles.h 3d_obj/*.h
	$(CC) -c scene.c -O3 -o scene.o

ray_marching.o : ray_marching.c ray_marching.h light.h vector.h options.h scene.h
	$(CC) -c ray_marching.c -O3 -o ray_marching.o

light.o : light.c light.h utiles.h vector.h scene.h
	$(CC) -c light.c -O3 -o light.o

dessin_fct.o : dessin_fct.h dessin_fct.c options.h light.h
	$(CC) -c dessin_fct.c -lglfw -lGL -O3 -o dessin_fct.o

# 3d obj
# 3d_obj/pingouin_1_sdf.o : 3d_obj/pingouin_1_sdf.h 3d_obj.pingouin_1_sdf.c vector.h utiles.h signed_distance_function.h
# 	$(CC) -c 3d_obj/pingouin_1_sdf.c -O3 -o 3d_obj/pingouin_1_sdf.o

3d_obj/pingouin_2_sdf.o : 3d_obj/pingouin_2_sdf.h 3d_obj.pingouin_2_sdf.c vector.h utiles.h signed_distance_function.h
	$(CC) -c 3d_obj/pingouin_2_sdf.c -O3 -o 3d_obj/pingouin_2_sdf.o

3d_obj/cube_sdf.o : 3d_obj/cube_sdf.h 3d_obj.cube_sdf.c vector.h utiles.h signed_distance_function.h
	$(CC) -c 3d_obj/cube_sdf.c -O3 -o 3d_obj/cube_sdf.o

test_ecran : main_test.c options.h vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o 3d_obj/*.o
	$(CC) main_test.c vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o 3d_obj/*.o -lm -lglfw -lGL -O3 -o test_ecran



clean : 
	rm -f ./test_ecran
	rm -f *.o
	rm -f 3d_obj/*.o


