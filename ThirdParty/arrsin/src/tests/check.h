template<class T>
void check(T vec)
{
	double sum = 0.0;
	for (auto elem : vec)
		sum += elem;
	printf("check sum = %f\n", sum);	
}
