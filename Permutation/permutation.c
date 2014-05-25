int factoriel(int k) {
	if(k == 1 || k == 0)
		return 1;
		
	return k * factoriel(k-1);
}

void func() {
	// array we want to permute
	int array[SIZE];
	
	int alreadyPlaces[SIZED * SIZED]; // array n * n to see if a value as already been in a specific place. aka: alreadyPlaces[index + SIZE * position] = 1 if the value at the index index as already been permuted to the position position
	
	for(i = 0 ; i<SIZED * SIZED ; ++i) {
		alreadyPlaces[i] = 0;
	}
	
	// temporary array for operations
	int temp[SIZE];
	int i = 0;
	
	int nbPermutation = factoriel(SIZE);
	
	// For an array of a size SIZE there is SIZE! permutation
	for(i=0 ; i<nbPermutation ; ++i) {
		
		// We want to edit the temporary array
		for(int j = 0 ; j< SIZE ; ++j) {
			// what index do we take ?
			int index;
			for(int k = 0 ; k < SIZE ; ++k) {
				// We choose an index that hasn't already been placed at the specific position
				if(alreadyPlaces[k + j * SIZE] == 0) {
					// We verify that the value isn't already in temp
					int alreadyIntTemp = 0;
					for(int m = 0 ; m < j ; ++m) {
						if(temp[m] == array[k])
							alreadyInTemp = 1;
					}
					
					if(alreadyInTemp == 0) {
						index = k;
						break;
					} 
				}
			}
			temp[j] = array[index];
			alreadyPlaces[index + j * SIZE] = 1;
		}
		
		// On fait le traitement avec temp
		traitement(temp);
		
	}
	

}


