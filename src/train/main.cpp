#include <iostream>
#include <fann.h>

int main()
{

	//fann * ann = fann_create_from_file("cardiogram.net");
	fann * ann = fann_create_standard(3, 3, 16, 5);

	fann_set_training_algorithm(ann, FANN_TRAIN_RPROP);
	fann_train_on_file(ann, "train.data", 100000, 100, 0.0001);

	fann_save(ann, "cardiogram.net");
	//fann* ann = fann_create_from_file("cardiogram.net");

	system("pause");

	return 0;
}