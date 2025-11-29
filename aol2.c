#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_DATA 4000

void displayMenu();

struct Data{
    char location1[100];
    char location2[100];
    unsigned int prices;
    unsigned int rooms;
    unsigned int bathrooms;
    unsigned int carParks;
    char type[100];
    char furnish[100];
};
typedef struct Data data;
data d[MAX_DATA];
char header[256];
int counter;

//fungsi ini untuk membaca file .csv yang berada pada direktori yang sama dengan kode program ini
//jika file tidak ditemukan, akan menampilkan error message dan program di terminasi
//data yang dimuat disimpan pada array of struct
//fungsi ini akan dipanggil saat program pertama kali dijalankan untuk memastikan struct tidak kosong dan ketika user memilih opsi export file, file jadi tidak akan kosong
void readData(){
    FILE* file;
    file = fopen("file.csv", "r");
    if(file == NULL){
    	printf("Can't open file!\n");
    	exit(0);
	}
    fgets(header, sizeof(header), file);
    int i = 0;
    while(!feof(file)){
        fscanf(file, "%[^,],%[^,],%u,%u,%u,%u,%[^,],%[^\n]\n", d[i].location1, d[i].location2, &d[i].prices, &d[i].rooms, &d[i].bathrooms, &d[i].carParks, d[i].type, d[i].furnish);
        i++;
    }
    counter = i;
    fclose(file);
}

//fungsi ini digunakan untuk menampilkan baris header untuk fungsi search
//fungsi untuk header ini dibuat terpisah untuk memudahkan penulisan (tidak perlu diketik berulang-ulang, cukup panggil fungsi)
//karena ada banyak kategori pencarian dan masing-masing kategori akan memerlukan header jadi supaya tidak perlu diketik berkali-kali maka dibuat fungsi
void printHeader(char query[], char column[]){
    printf("Data found. Detail of data with query \"%s\" from category \"%s\":\n", query, column);
    printf("%-25s %-15s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");
        for(int i = 0; i < 110; i++){
    	printf("=");
	}
	printf("\n");
}

//fungsi untuk export data, fungsi akan mencetak data dari struct ke file yang namanya ditentukan user dalam format csv
//jika data tidak dimuat di awal program maka struct kosong, file yang diekspor juga akan kosong
//maka dari itu di awal dipanggil fungsi untuk memuat data terlebih dahulu
//jika fungsi ini dijalankan tepat di awal setelah program di-run, maka hasil export file akan sama dengan file original
//namun jika sebelumnya user sudah menjalankan fungsi sort, isi file yang diekspor akan terurut berdasarkan kategori yang diinginkan user
void exportFile(char filename[]){
    FILE* export;
    export = fopen(filename, "w");
    fputs(header, export);
    for(int i = 0; i < counter; i++){
        fprintf(export, "%s,%s,%u,%u,%u,%u,%s,%s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
    }
    fclose(export);
    printf("Data saved successfully to file %s!\n", filename);
    printf("\n");
    displayMenu();
}

//fungsi merge merupakan bagian dari algoritma merge sort untuk menggabung-gabungkan subarray yang sudah terurut ke array utama
//di dalamnya terdapat decision structure supaya program mampu mengurutkan berdasarkan kolom/kategori dan tipe (ascending/descending) sesuai inputan user
void merge(int left, int mid, int right, char column[], char type[]){
    int l = mid - left + 1;
    int r = right - mid;
    data L[l];
    data R[r];
    
    for(int i = 0; i < l; i++){
        L[i] = d[left + i];
    }
    for(int j = 0; j < r; j++){
        R[j] = d[mid + 1 + j];
    }

    if(strcmp(type, "asc") == 0){
        if(strcmp(column, "location") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(strcmp(L[i].location1, R[j].location1) <= 0){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "city") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(strcmp(L[i].location2, R[j].location2) <= 0){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "price") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(L[i].prices <= R[j].prices){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "rooms") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(L[i].rooms <= R[j].rooms){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "bathroom") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(L[i].bathrooms <= R[j].bathrooms){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "carpark") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(L[i].carParks <= R[j].carParks){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "type") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(strcmp(L[i].type, R[j].type) <= 0){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "furnish") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(strcmp(L[i].furnish, R[j].furnish) >= 0){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }
    }else if(strcmp(type, "des") == 0){
        if(strcmp(column, "location") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(strcmp(L[i].location1, R[j].location1) >= 0){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "city") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(strcmp(L[i].location2, R[j].location2) >= 0){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "price") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(L[i].prices >= R[j].prices){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "rooms") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(L[i].rooms >= R[j].rooms){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "bathroom") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(L[i].bathrooms >= R[j].bathrooms){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "carpark") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(L[i].carParks >= R[j].carParks){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "type") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(strcmp(L[i].type, R[j].type) >= 0){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }else if(strcmp(column, "furnish") == 0){
            int i = 0, j = 0, k = left;
            while(i < l && j < r){
                if(strcmp(L[i].furnish, R[j].furnish) <= 0){
                    d[k] = L[i];
                    i++;
                }else{
                    d[k] = R[j];
                    j++;
                }
                k++;
            }

            while(i < l){
                d[k] = L[i];
                i++;
                k++;
            }
            while(j < r){
                d[k] = R[j];
                j++;
                k++;
            }
        }
    }
}

//fungsi mergeSort untuk proses algoritma merge sort pada umumnya, dengan tambahan parameter kolom dan tipe
//supaya program mampu mengurutkan berdasarkan keinginan user
//alasan menggunakan merge sort karena jumlah data cukup banyak yakni 3900an data
//maka diperlukan algoritma sorting yang efisien
void mergeSort(int left, int right, char column[], char type[]){
    if(left >= right){
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(left, mid, column, type);
    mergeSort(mid + 1, right, column, type);
    merge(left, mid, right, column, type);
}

//fungsi untuk menampilkan data yang sudah terurut berdasarkan kolom dan tipe tertentu sesuai inputan user
//proses sorting dilakukan pada fungsi terpisah untuk modularisasi kode
void sortData(char column[], char type[]){
    mergeSort(0, counter - 1, column, type);
    if(strcmp(type, "asc") == 0){
    	printf("Here are the first 10 lists of the sorted data by category \"%s\" (Ascending):\n", column);
	}else{
		printf("Here are the first 10 lists of the sorted data by category \"%s\" (Descending):\n", column);
	}
	printf("%-25s %-15s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");
	for(int i = 0; i < 110; i++){
    	printf("=");
	}
	printf("\n");
    for(int i = 0; i < 10; i++){
        printf("%-25s %-15s %-10u %-10u %-10u %-10u %-10s %-10s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
    }
    printf("\n");
    displayMenu();
}

//fungsi untuk melakukan pencarian data sesuai kategori yang diinginkan user, secara keseluruhan menggunakan linear search
//semua hasil yang sesuai akan ditampilkan, namun jika tidak ada yang sesuai maka program akan menampilkan error message
//di dalamnya terdapat decision structure juga seperti pada sorting
//yang memungkinkan program untuk mencari berdasarkan kolom dan query tertentu
void searchData(char column[], char query[]){
    int count = 0;
    if(strcmp(column, "location") == 0){
        for(int i = 0; i < counter; i++){
            if(strcmp(d[i].location1, query) == 0){
                count++;
            }
        }
        if(count != 0){
            printHeader(query, column);
            for(int i = 0; i < counter; i++){
                if(strcmp(d[i].location1, query) == 0){
                    printf("%-25s %-15s %-10u %-10u %-10u %-10u %-10s %-10s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
                }
            }
        }else{
        	printf("Data not found!\n");
        }
    }else if(strcmp(column, "city") == 0){
        for(int i = 0; i < counter; i++){
            if(strcmp(d[i].location2, query) == 0){
                count++;
            }
        }
        if(count != 0){
            printHeader(query, column);
            for(int i = 0; i < counter; i++){
                if(strcmp(d[i].location2, query) == 0){
                    printf("%-25s %-15s %-10u %-10u %-10u %-10u %-10s %-10s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
                }
            }
        }else{
        	printf("Data not found!\n");
        }
    }else if(strcmp(column, "price") == 0){
        unsigned int query1 = atoi(query);
        for(int i = 0; i < counter; i++){
            if(d[i].prices == query1){
                count++;
            }
        }
        if(count != 0){
            printHeader(query, column);
            for(int i = 0; i < counter; i++){
                if(d[i].prices == query1){
                    printf("%-25s %-15s %-10u %-10u %-10u %-10u %-10s %-10s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
                }
            }
        }else{
        	printf("Data not found!\n");
        }
    }else if(strcmp(column, "rooms") == 0){
        unsigned int query1 = atoi(query);
        for(int i = 0; i < counter; i++){
            if(d[i].rooms == query1){
                count++;
            }
        }
        if(count != 0){
            printHeader(query, column);
            for(int i = 0; i < counter; i++){
                if(d[i].rooms == query1){
                    printf("%-25s %-15s %-10u %-10u %-10u %-10u %-10s %-10s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
                }
            }
        }else{
        	printf("Data not found!\n");
        }
    }else if(strcmp(column, "bathroom") == 0){
        unsigned int query1 = atoi(query);
        for(int i = 0; i < counter; i++){
            if(d[i].bathrooms == query1){
                count++;
            }
        }
        if(count != 0){
            printHeader(query, column);
            for(int i = 0; i < counter; i++){
                if(d[i].bathrooms == query1){
                    printf("%-25s %-15s %-10u %-10u %-10u %-10u %-10s %-10s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
                }
            }
        }else{
        	printf("Data not found!\n");
        }
    }else if(strcmp(column, "carpark") == 0){
        unsigned int query1 = atoi(query);
        for(int i = 0; i < counter; i++){
            if(d[i].carParks == query1){
                count++;
            }
        }
        if(count != 0){
            printHeader(query, column);
            for(int i = 0; i < counter; i++){
                if(d[i].carParks == query1){
                    printf("%-25s %-15s %-10u %-10u %-10u %-10u %-10s %-10s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
                }
            }
        }else{
        	printf("Data not found!\n");
        }
    }else if(strcmp(column, "type") == 0){
        for(int i = 0; i < counter; i++){
            if(strcmp(d[i].type, query) == 0){
                count++;
            }
        }
        if(count != 0){
            printHeader(query, column);
            for(int i = 0; i < counter; i++){
                if(strcmp(d[i].type, query) == 0){
                    printf("%-25s %-15s %-10u %-10u %-10u %-10u %-10s %-10s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
                }
            }
        }else{
        	printf("Data not found!\n");
        }
    }else if(strcmp(column, "furnish") == 0){
        for(int i = 0; i < counter; i++){
            if(strcmp(d[i].furnish, query) == 0){
                count++;
            }
        }
        if(count != 0){
            printHeader(query, column);
            for(int i = 0; i < counter; i++){
                if(strcmp(d[i].furnish, query) == 0){
                    printf("%-25s %-15s %-10u %-10u %-10u %-10u %-10s %-10s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
                }
            }
        }else{
        	printf("Data not found!\n");
        }
    }
    printf("\n");
    displayMenu();
}

//fungsi ini untuk menampilkan data sebanyak n baris sesuai inputan user
//jika program pertama dijalankan akan menampilkan data sebanyak n baris yang masih belum terurut
//jika user sudah memilih opsi sort data kemudian kembali menampilkan data menggunakan fungsi ini
//maka program akan menampilkan data yang sudah terurut berdasarkan kategori yang diinginkan user
void displayData(int lot){
	printf("Here are the first %d row(s) of the data:\n", lot);
    printf("%-25s %-15s %-10s %-10s %-10s %-10s %-10s %-10s\n", "Location", "City", "Price", "Rooms", "Bathroom", "Carpark", "Type", "Furnish");
    for(int i = 0; i < 110; i++){
    	printf("=");
	}
	printf("\n");
    for (int i = 0; i < lot; i++){
        printf("%-25s %-15s %-10u %-10u %-10u %-10u %-10s %-10s\n", d[i].location1, d[i].location2, d[i].prices, d[i].rooms, d[i].bathrooms, d[i].carParks, d[i].type, d[i].furnish);
    }
    printf("\n");
    displayMenu();
}

//fungsi ini hanya untuk menampilkan judul "main menu" dengan dekorasi
void printTitle(){
	char header[][100] =
	{
		"===============",
		"|| Main Menu ||",
		"==============="
	};
	int rows = sizeof(header) / sizeof(header[0]);
	int columns = sizeof(header[0]) / sizeof(header[0][0]);
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			printf("%c", header[i][j]);
		}
		printf("\n");
	}
}

//fungsi ini untuk menampilkan initial menu yang berisi opsi utama untuk operasi data seperti tampilkan data, cari data, urutkan data dan ekspor file
//di dalamnya terdapat validasi input (walau belum sempurna) untuk menghandle input yang disengaja atau tidak disengaja salah
//dan juga terdapat informasi untuk membantu user mengetahui input apa saja yang bisa diterima program
//menggunakan switch case untuk inputan opsi dari user dan input yang diterima berupa angka 1-5
//diluar itu (kasus default) fungsi ini akan memanggil dirinya sendiri sebagai bentuk error handling
void displayMenu(){
    int choice;
    printTitle();
    printf("Select Option:\n1. Display Data\n2. Search Data\n3. Sort Data\n4. Export Data\n5. Exit\n");
    printf(">> ");
    scanf("%d", &choice); getchar();
	printf("\n");
    switch(choice){
        case 1:{
            int lot;
            do{
                printf("Number of rows to be displayed: ");
                scanf("%d", &lot); getchar();
                if(lot < 1){
                    printf("Number is invalid. Must be greater than 0.\n\n");
                }
            }while(lot < 1);
            if(lot > counter){
                lot = counter;
            }
            printf("\n");
            displayData(lot);
            break;
        }
        case 2:{
            char column[100];
            input:
            printf("Available category to search by:\n> Location\n> City\n> Price\n> Rooms (Total rooms)\n> Bathroom (Total bathroom)\n> Carpark (Total parking space)\n> Type\n> Furnish\n");
            printf("Type category: ");
	        scanf("%[^\n]", column); getchar();
	    	for(int i = 0; i < strlen(column); i++){
	        	column[i] = tolower(column[i]);
	        }
	        if(column[0] == 'l'){
	        	strcpy(column, "location");
			}else if(column[0] == 'c' && column[1] == 'i'){
				strcpy(column, "city");
			}else if(column[0] == 'p'){
				strcpy(column, "price");
			}else if(column[0] == 'r'){
				strcpy(column, "rooms");
			}else if(column[0] == 'b'){
				strcpy(column, "bathroom");
			}else if(column[0] == 'c' && column[1] == 'a'){
				strcpy(column, "carpark");
			}else if(column[0] == 't'){
				strcpy(column, "type");
			}else if(column[0] == 'f'){
				strcpy(column, "furnish");
			}else{
				printf("Invalid input!\n\n");
				goto input;
			}
            char query[100];
            if(strcmp(column, "type") == 0){
            	printf("Available types are:\n> Built-up\n> Land-area\n");
			}else if(strcmp(column, "furnish") == 0){
				printf("Available furnishes are:\n> Unfurnished\n> Partly\n> Fully\n");
			}
			if(strcmp(column, "location") == 0){
				printf("Be aware of the uppercase and lowercase letter for some location!\nIf you're not sure, try to display the data first\n");
				printf("Query to be found: ");
			}else{
				printf("Query to be found: ");
			}
            scanf("%[^\n]", query); getchar();
            query[0] = toupper(query[0]);
            for(int i = 0; query[i] != '\0'; i++){
            	if(query[i] == ' '){
            		query[i] = '-';
				}
			}
			if(strcmp(column, "location") == 0 || strcmp(column, "city") == 0){
				for(int i = 0; query[i] != '\0'; i++){
					if(query[i] == '-'){
						query[i + 1] = toupper(query[i + 1]);
					}
				}
			}
            printf("\n");
            searchData(column, query);
            break;
        }
        case 3:{
            char column[100];
            input1:
			printf("Available category to sort by:\n> Location\n> City\n> Price\n> Rooms (Total rooms)\n> Bathroom (Total bathroom)\n> Carpark (Total parking space)\n> Type\n> Furnish\n");
            printf("Type category: ");
	        scanf("%[^\n]", column); getchar();
	        for(int i = 0; i < strlen(column); i++){
	            column[i] = tolower(column[i]);
	        }
	        if(column[0] == 'l'){
	        	strcpy(column, "location");
			}else if(column[0] == 'c' && column[1] == 'i'){
				strcpy(column, "city");
			}else if(column[0] == 'p'){
				strcpy(column, "price");
			}else if(column[0] == 'r'){
				strcpy(column, "rooms");
			}else if(column[0] == 'b'){
				strcpy(column, "bathroom");
			}else if(column[0] == 'c' && column[1] == 'a'){
				strcpy(column, "carpark");
			}else if(column[0] == 't'){
				strcpy(column, "type");
			}else if(column[0] == 'f'){
				strcpy(column, "furnish");
			}else{
				printf("Invalid input!\n\n");
				goto input1;
			}
            char type[100];
            input2:
            printf("Ascending (asc) or descending (des): ");
	        scanf("%[^\n]", type); getchar();
	        for(int i = 0; i < strlen(type); i++){
	            type[i] = tolower(type[i]);
	        }
	        if(type[0] == 'a'){
	        	strcpy(type, "asc");
			}else if(type[0] == 'd'){
				strcpy(type, "des");
			}else{
				printf("Invalid input!\n\n");
				goto input2;
			}
            printf("\n");
            sortData(column, type);
            break;
        }
        case 4:{
            char filename[100];
            printf("File name: ");
            scanf("%[^\n]", filename); getchar();
            strcat(filename, ".csv");
            printf("\n");
            exportFile(filename);
            break;
        }
        case 5:{
        	printf("Thank you!\n");
            exit(0);
            break;
        }
        default:{
            printf("Invalid option!\n\n");
            displayMenu();
            break;
        }
    }
}

int main(){
    readData();		//pemanggilan fungsi readData ketika program pertama dijalankan seperti sudah dijelaskan diatas
    displayMenu();	//pemanggilan fungsi untuk menampilkan initial menu
    return 0;		//setiap sebuah fungsi selesai dijalankan akan kembali memanggil fungsi displayMenu untuk kembali ke main menu
}					/*alasannya initial menu tidak disimpan pada fungsi main
					karena logikanya setiap sebuah fungsi selesai melaksanakan tugasnya, akan memanggil fungsi yang memuat initial menu untuk ditampilkan lagi
					jika initial menu disimpan di main, maka fungsi yang harus dipanggil adalah fungsi main
					sementara fungsi main memuat pemanggilan readData, maka setiap kali program kembali ke main menu dengan memanggil fungsi main
					fungsi readData akan kembali dipanggil juga
					hal ini akan mengakibatkan struct yang sudah diurutkan misalnya, tertimpa oleh file original yang belum diurutkan
					karena fungsi readData memuat lagi data originalnya
					maka dari itu dibuat fungsi tersendiri untuk menampilkan initial menu*/
