int is_prime(int n){
	if (n%2 == 0 || n==1)
		return 0;

	for(int  i=3;i<n;i+=2){
		if(n%i==0){
			return 0;
		}
	}
	return 1;
}
