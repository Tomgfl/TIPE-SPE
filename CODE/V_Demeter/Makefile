# test_ecran : main_test.c dessin_fct.c options.h vector.c signed_distance_function.c utiles.c light.c scene.c 3d_obj/*.c ray_marching.c 
# 	gcc main_test.c dessin_fct.c vector.c utiles.c ray_marching.c signed_distance_function.c light.c scene.c 3d_obj/*.c -O3 -lm -lglfw -lGL -o test_ecran

CC = clang
OPTIONS = -O3 -ffast-math -g -fsanitize=address
ADD = -lglfw -lGL -pthread -lm
ALL_O = vector.o utiles.o signed_distance_function.o scene.o ray_marching.o light.o dessin_fct.o pingouin_sdf.o nurbs.o

all : test_ecran main_1 main_2 main_3 main_4 main_5

vector.o : vector.c vector.h options.h
	$(CC) -c vector.c $(OPTIONS) -o vector.o

utiles.o : utiles.c utiles.h options.h
	$(CC) -c utiles.c $(OPTIONS) -o utiles.o

signed_distance_function.o : signed_distance_function.c signed_distance_function.h vector.h utiles.h options.h
	$(CC) -c signed_distance_function.c $(OPTIONS) -o signed_distance_function.o

scene.o : scene.h scene.c vector.h signed_distance_function.h utiles.h pingouin_sdf.h options.h nurbs.h
	$(CC) -c scene.c $(OPTIONS) -o scene.o

ray_marching.o : ray_marching.c ray_marching.h light.h vector.h options.h scene.h
	$(CC) -c ray_marching.c $(OPTIONS) -o ray_marching.o

light.o : light.c light.h utiles.h vector.h scene.h options.h 
	$(CC) -c light.c $(OPTIONS) -o light.o

dessin_fct.o : dessin_fct.h dessin_fct.c options.h light.h
	$(CC) -c dessin_fct.c $(OPTIONS) -o dessin_fct.o


pingouin_sdf.o : pingouin_sdf.h pingouin_sdf.c options.h vector.h utiles.h signed_distance_function.h
	$(CC) -c pingouin_sdf.c $(OPTIONS) -o pingouin_sdf.o

nurbs.o : nurbs.c nurbs.h options.h vector.h vector.c
	$(CC) -c nurbs.c $(OPTIONS) $(ADD) -o nurbs.o

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

test_ecran : main_test.c options.h $(ALL_O)
	$(CC) main_test.c $(ALL_O) $(OPTIONS) $(ADD) -o test_ecran


main_1 : main_1.c options.h $(ALL_O)
	$(CC) main_1.c $(ALL_O) $(OPTIONS) $(ADD) -o main_1

main_2 : main_2.c options.h $(ALL_O)
	$(CC) main_2.c $(ALL_O) $(OPTIONS) $(ADD) -o main_2

main_3 : main_3.c options.h $(ALL_O)
	$(CC) main_3.c $(ALL_O) $(OPTIONS) $(ADD) -o main_3

main_4 : main_4.c options.h $(ALL_O)
	$(CC) main_4.c $(ALL_O) $(OPTIONS) $(ADD) -o main_4

main_5 : main_5.c options.h $(ALL_O)
	$(CC) main_5.c $(ALL_O) $(OPTIONS) $(ADD) -o main_5

clean : 
	rm -f ./test_ecran
	rm -f *.o
	rm -f main_1 main_2 main_3 main_4 main_5 test_ecran
# rm -f 3d_obj/*.o


