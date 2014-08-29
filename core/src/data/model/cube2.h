//cube.obj

int cube2_num_vertices = 24;
int cube2_num_indices = 36;

double cube2_vertices[] = {
	-512, 480, 0.0, 0.0, 1.0,  0.0, 0.0, 1.0,
	-512, -480, 0.0, 0.0, 0.0,  0.0, 0.0, 1.0,
	512, 480, 0.0, 1.0, 1.0,  0.0, 0.0, 1.0,
	512, -480, 0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
	512, -480, -51.5912, 0.0, 0.0,  0.0, 0.0, -1.0,
	-512, -480, -51.5912, 1.0, 0.0,  0.0, 0.0, -1.0,
	512, 480, -51.5912, 0.0, 1.0,  0.0, 0.0, -1.0,
	-512, 480, -51.5912, 1.0, 1.0,  0.0, 0.0, -1.0,
	512, -480, 0.0, 1.0, 0.0,  0.0, -1.0, 0.0,
	-512, -480, 0.0, 0.0, 0.0,  0.0, -1.0, 0.0,
	512, -480, -51.5912, 1.0, 1.0,  0.0, -1.0, 0.0,
	-512, -480, -51.5912, 0.0, 1.0,  0.0, -1.0, 0.0,
	512, 480, 0.0, 1.0, 0.0,  1.0, 0.0, 0.0,
	512, -480, 0.0, 0.0, 0.0,  1.0, 0.0, 0.0,
	512, 480, -51.5912, 1.0, 1.0,  1.0, 0.0, 0.0,
	512, -480, -51.5912, 0.0, 1.0,  1.0, 0.0, 0.0,
	-512, 480, 0.0, 1.0, 0.0,  0.0, 1.0, 0.0,
	512, 480, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0,
	-512, 480, -51.5912, 1.0, 1.0,  0.0, 1.0, 0.0,
	512, 480, -51.5912, 0.0, 1.0,  0.0, 1.0, 0.0,
	-512, -480, 0.0, 1.0, 0.0,  -1.0, 0.0, 0.0,
	-512, 480, 0.0, 0.0, 0.0,  -1.0, 0.0, 0.0,
	-512, -480, -51.5912, 1.0, 1.0,  -1.0, 0.0, 0.0,
	-512, 480, -51.5912, 0.0, 1.0,  -1.0, 0.0, 0.0
};
short cube2_indices[] = {
	0, 1, 2, 
	3, 2, 1, 
	4, 5, 6, 
	7, 6, 5, 
	8, 9, 10, 
	11, 10, 9, 
	12, 13, 14, 
	15, 14, 13, 
	16, 17, 18, 
	19, 18, 17, 
	20, 21, 22, 
	23, 22, 21
};