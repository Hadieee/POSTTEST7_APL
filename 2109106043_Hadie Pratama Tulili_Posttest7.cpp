#include <iostream> // Untuk penggunaan fungsi cout, cin, dan endl
#include <conio.h>  // Untuk penggunaan fungsi getch
#include <iomanip>  // Untuk merapikan spasi membuat table
#include <fstream>  // Untuk membaca, menulis, serta membuat file eksternal
#include <sstream>  // Untuk convert tipe data string ke tipe data lain
using namespace std; // Agar tidak perlu menuliskan "std::"

struct anggota // Terdapat sebuah struct untuk mendeklarasi array dari nama, jenis kelamin, umur dan ketersediaan raket
{
    string nama;
    string kelamin;
    int umur;
    int ketersediaan;
};

// Untuk mendeklarasikan sebuah array data_anggota yang bertipe struct data
struct anggota data_anggota[50]; 

// Untuk keperluan pertambahan indeks array, panjang array, nomor, pilihan, perulangan, penukaran, dan membandingkan
int a = 0, b, c, i, j, m = sizeof(data_anggota)/sizeof(data_anggota[0]), min_index, ditemukan = 0, pilih; 

// Untuk tanya saat ingin keluar dari program serta memilih jenis pengurutan
char tanya, urut; 

// Untuk variabel saat mencari nama
string Nama;

// Untuk menulis(write),membaca(read),membuat(create) serta menghapus(delete) file.
fstream myFile;
fstream temp;

//Prototype
void inputdata(anggota arr[]);
void lihatdata(anggota arr[]);
void editdata(anggota arr[]);
void hapusdata(anggota arr[]);
void hapusfile(anggota arr[]);
void urutan();
void bubble_sort_Umur_Asc(anggota arr[]);
void bubble_sort_Umur_Desc(anggota arr[]);
void bubble_sort_Raket_Asc(anggota arr[], int n);
void bubble_sort_Raket_Desc(anggota arr[]);
void selection_sort_Umur_Asc(anggota arr[], int n);
void selection_sort_Umur_Desc(anggota arr[], int n);
void selection_sort_Raket_Asc(anggota arr[], int n);
void selection_sort_Raket_Desc(anggota arr[], int n);
void insertion_sort_Umur_Asc(anggota arr[], int n);
void insertion_sort_Umur_Desc(anggota arr[], int n);
void insertion_sort_Raket_Asc(anggota arr[], int n, int tipe);
void insertion_sort_Raket_Desc(anggota arr[], int n);
void selectionSort(anggota arr[], int n);
void binarySearch(anggota arr[], int low, int high);
void interpolation_search(anggota arr[], int jumlahData);
void tampilan_sorting_Asc();
void tampilan_sorting_Desc();
void tampilan_searching();
void openfile();

// Fungsi utama
int main() 
{
    // Terdapat label awal sebagai tempat untuk kembali ke menu utama setelah melakukan eksekusi data
    awal: 
    system("cls");
    system("color 5A");
    cout<<"\n============================= PROGRAM CRUD DATA ANGGOTA =============================";
    cout<<"\n=================================== PILIHAN MENU ====================================\n";
    cout<<"\n\t\t\t\t1. Masukkan data";
    cout<<"\n\t\t\t\t2. Lihat Data";
    cout<<"\n\t\t\t\t3. Edit Data";
    cout<<"\n\t\t\t\t4. Hapus Data";
    cout<<"\n\t\t\t\t5. Hapus File Eksternal";   
    cout<<"\n\t\t\t\t6. Sorting Data";
    cout<<"\n\t\t\t\t7. Search Data"; 
    cout<<"\n\t\t\t\t8. Keluar\n";
    cout<<"\n=====================================================================================\n";
    cout<<"\nMasukkan Pilihan : ";
    pilih = getch();
    switch(pilih)
    {
        case'1':
            // goto yang berfungsi untuk melompat ke baris label
            {system("cls");inputdata(data_anggota);goto awal;} 
        case'2':
            // goto yang berfungsi untuk melompat ke baris label
            {system("cls");lihatdata(data_anggota);goto awal;}
        case'3':
            // goto yang berfungsi untuk melompat ke baris label
            {system("cls");editdata(data_anggota);goto awal;}
        case'4':
            // goto yang berfungsi untuk melompat ke baris label
            {system("cls");hapusdata(data_anggota);goto awal;}
        case'5':
            {system("cls");hapusfile(data_anggota);goto awal;}
        case'6':
            // goto yang berfungsi untuk melompat ke baris label
            {system("cls");urutan();goto awal;}
        case'7':
            // goto yang berfungsi untuk melompat ke baris label
            {system("cls");tampilan_searching();goto awal;}        
        case'8':
            {   
                system("cls");
                // Terdapat label Tanya sebagai tempat untuk kembali ke pilihan ingin keluar program ketika salah dalam memilih
                Tanya: 
                
                cout<<"\nApakah anda ingin keluar dari program ? (Y / T) : "<< endl; // Untuk menanyakan user apakah ingin keluar dari program
                tanya = getch();
                switch (tanya)
                {
                    case('y'):
                    case('Y'):
                        system("cls");
                        cout<<"=======================================================================" << endl;
                        cout << "Terimakasih telah menggunakan program ini :) Semoga harimu menyenangkan" << endl;
                        cout<<"======================================================================="; exit(0);

                    case('t'):
                    case('T'):
                        system("cls");goto awal;
                    
                    // Untuk kesalahan dalam memilih
                    default: 
                        cout<<"Pilihan yang anda masukkan salah, Mohon pilih kembali";getch();goto Tanya;
                }
                }
        // Untuk kesalahan dalam memilih
        default:
        {
            cout<<"Pilihan yang anda masukkan salah, Mohon pilih kembali";getch();goto awal;
        }
    }
}

// Fungsi untuk int error handling
int checkInt()
{
	int var;
	cin >> var;

    if(cin.fail())
    {
        cout << "\tInputan tersebut bukan angka" << endl;
        cin.clear();
        cin.ignore();
    }
    
    return var;
}


void openfile()
{
    myFile.open("data_anggota.csv", ios::out);
    // jika file nya belum ada maka dibuatkan
    if (!myFile.is_open())
    {
        // Jika file digunakan untuk operasi output dan file telah ada sebelumnya, content sebelumnya akan dihapus.
        myFile.open("data_anggota.csv", ios::trunc);
        myFile.close();
    }
    myFile.close();
}


// Prosedur untuk input data
void inputdata(anggota arr[])
{
    // openfile();
    myFile.open("data_anggota.csv", ios::out | ios::app);

    system("color 5A");
    cout<<"Nama Panggilan\t\t\t\t: "; getline(cin,data_anggota[a].nama);fflush(stdin);
    cout<<"Jenis Kelamin (L / P)\t\t\t: ";cin>>data_anggota[a].kelamin;fflush(stdin);
    cout<<"Umur\t\t\t\t\t: ";data_anggota[a].umur = checkInt();fflush(stdin);
    cout<<"Jumlah ketersediaan Raket\t\t: ";data_anggota[a].ketersediaan = checkInt();fflush(stdin);

    myFile << arr[a].nama << "," << arr[a].kelamin << "," << arr[a].umur << "," << arr[a].ketersediaan << endl;

    // Untuk penambahan indeks array
    a++; 
    cout<<"\n=========================== Data Berhasil Ditambahkan ===========================";
    getch();system("cls");
    myFile.close();
}


// Prosedur untuk lihat data
void lihatdata(anggota arr[]) 
{
    // Membaca file eksternal
    myFile.open("data_anggota.csv", ios::in);
    if (myFile.fail())
    {   
        cout << "Maaf, file tidak dapat dibuka / tidak ditemukan";
        myFile.close();
    }
    j = 0;
    string umur, ketersediaan;
    system("color 5A");
    cout<<"\n========================================================= Menampilkan Data ===================================================================\n\n";
    cout<<"==============================================================================================================================================\n";
    cout<<"||"<<setw(5)<<"NO"<<setw(5)<<"||"<<setw(25)<<"Nama Panggilan"<<setw(15)<<"||"<<setw(25)<<"Jenis Kelamin"<<setw(15)<<"||"<<setw(10)<<"Umur"<<setw(10)<<"||"<<setw(20)<<"Ketersediaan"<<setw(10)<<"||";
    cout<<"\n==============================================================================================================================================";
    
    for(i = 0;i < 50;i++)
    {
        getline(myFile, arr[i].nama, ',');
        getline(myFile, arr[i].kelamin, ',');
        getline(myFile, umur, ',');
        getline(myFile, ketersediaan, '\n');
        
        // untuk convert string ke tipe data lain
        stringstream umurstring(umur);
        stringstream ketersediaanstring(ketersediaan);
        umurstring >> arr[i].umur;
        ketersediaanstring >> arr[i].ketersediaan;

        if (myFile.eof())
        {
            break;
        }

        cout<<"\n||"<<setw(4)<< j + 1<<setw(6)<<"||";
        cout<<setw(25)<<arr[i].nama<<setw(15)<<"||";
        cout<<setw(20)<<arr[i].kelamin<<setw(20)<<"||";
        cout<<setw(10)<<arr[i].umur<<setw(10)<<"||";
        cout<<setw(15)<<arr[i].ketersediaan<<setw(15)<<"||";
        cout<<"\n==============================================================================================================================================";
        j++;
    }

    getch();system("cls");
    myFile.close();
}


void editdata(anggota arr[]) // Prosedur untuk edit data
{
    // Terdapat label apa sebagai tempat untuk kembali mengedit data ketika salah dalam memilih pilihan
    apa:
    system("cls");
    system("color 5A");
    cout<<"Masukan nama yang ingin diedit\t\t: "; getline(cin, Nama);
    
    for(b = 0; b < 50; b++)
    {
        if(arr[b].nama == Nama)
        {
            cout<<"Nama Panggilan\t\t\t\t: "; getline(cin,arr[b].nama); fflush(stdin);
            cout<<"Jenis Kelamin (L / P)\t\t\t: ";cin>>arr[b].kelamin; fflush(stdin);
            cout<<"Umur\t\t\t\t\t: ";arr[b].umur = checkInt(); fflush(stdin);
            cout<<"Jumlah ketersediaan Raket\t\t: "; arr[b].ketersediaan = checkInt();fflush(stdin);

            cout<<"\n========================================================== Data berhasil diedit ============================================================\n";
            ditemukan++;

            // buka file untuk re-write
            myFile.open("data_anggota.csv", ios::out);
            if (myFile.fail())
            {   
                cout << "\nMaaf, file tidak dapat dibuka / tidak ditemukan\n";
                myFile.close();
            }

            // write ulang semua data
            for (int i=0; i<50; i++) 
            {
                if(arr[i].nama == "")
                {
                    break;
                }

                else
                {
                    myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
                }

            }
            myFile.close();
            break;
        }
    }
        
        if (b == 50 - 2)
        {
            cout<<"Nama tidak ditemukan";

             // Untuk menanyakan user apakah ingin mengedit data lagi
            cout<<"\nApakah anda ingin mengedit kembali ? (Y / T) : "<< endl;
            tanya = getch();
            switch (tanya)
            {
                case('y'):
                case('Y'):
                    system("cls");myFile.close();goto apa;

                case('t'):
                case('T'):
                    break;
                
                // Untuk kesalahan dalam memilih
                default: 
                    cout<<"Pilihan yang anda masukkan salah, Mohon pilih kembali";getch();goto apa;
            }
        }         
    lihatdata(data_anggota);
}


// Prosedur untuk hapus data
void hapusdata(anggota arr[]) 
{
    // Terdapat label iya sebagai tempat untuk kembali menghapus data ketika salah dalam memilih pilihan
    iya: 
    system("color 5A");
    cout<<"Masukan nama yang ingin dihapus\t\t: "; getline(cin, Nama);

    for( c = 0; c < 50 - 1; c++)
    {
        if (arr[c].nama == Nama)
        {
            // Variabel a untuk indeks di data
            a--; 
            for(int i=c;i<a;i++)
            {
                arr[i] = arr[i+1];
            }
            system("cls");
            cout<<"\n========================================================== Data berhasil dihapus ============================================================\n";
            ditemukan++;


            // buka file untuk re-write
            myFile.open("data_anggota.csv", ios::out);
            if (myFile.fail())
            {   
                cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
                myFile.close();
            }

            // write ulang semua data
            for (int i=0; i<50; i++) 
            {
                if(arr[i].nama == "" or arr[i].nama == Nama)
                {
                    break;
                }

                else
                {
                    myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
                }

            }
            myFile.close();
            break;
        }
    }


        if(c == 50 - 2)
        {
            cout<<"Nama tidak ditemukan";

            // Untuk menanyakan user apakah ingin menghapus data lagi
            cout<<"\nApakah anda ingin mengedit kembali ? (Y / T) : "<< endl; 
            tanya = getch();
            switch (tanya)
            {
                case('y'):
                case('Y'):
                    system("cls");myFile.close();goto iya;

                case('t'):
                case('T'):
                    break;
                
                // Untuk kesalahan dalam memilih
                default: 
                    cout<<"Pilihan yang anda masukkan salah, Mohon pilih kembali";getch();goto iya;
            }
        }

    lihatdata(data_anggota);
    myFile.close();
}

// Prosedur untuk hapus data
void hapusfile(anggota arr[]) 
{
    // Terdapat label iya sebagai tempat untuk kembali menghapus data ketika salah dalam memilih pilihan
    iya: 
    system("color 5A");
    // Untuk menanyakan user apakah ingin menghapus file eksternal
    cout<<"Apakah anda yakin ingin menghapus file ? (Y / T): ";
    tanya = getch();
    switch (tanya)
    {
        case('y'):
        case('Y'):
            system("cls");cout<<"\n========================================================== Data berhasil dihapus ============================================================\n";
            remove("data_anggota.csv");getch();system("cls");break;

        case('t'):
        case('T'):
            break;
        
        // Untuk kesalahan dalam memilih
        default: 
            cout<<"Pilihan yang anda masukkan salah, Mohon pilih kembali";getch();goto iya;
    }
    myFile.close();
}

//prosedur algoritma bubble_sort secara ascending
void bubble_sort_Umur_Asc(anggota arr[])
{
	for(int i = 0; i < 48; i++)
    {
		for(int j = 0; j < 48; j++)
        {
			if(arr[j].umur > arr[j+1].umur &&
			(arr[j].umur != 0 && arr[j+1].umur != 0))
            {
				swap(arr[j], arr[j+1]);
            }			
		}
    
        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }
    //data umur berhasil disorting dengan menggunakan algoritma bubble sort 
    cout<<"bubble sort selesai !"<<endl; 
}


//prosedur algoritma bubble_sort secara descending
void bubble_sort_Umur_Desc(anggota arr[])
{
	for(int i = 0; i < 48; i++){
		for(int j = 0; j < 48; j++){
			if(arr[j].umur < arr[j+1].umur &&
			(arr[j].umur != 0 && arr[j+1].umur != 0))
            {
				swap(arr[j], arr[j+1]);
            }			
		}

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }

    //data umur berhasil disorting dengan menggunakan algoritma bubble sort 
    cout<<"bubble sort selesai !"<<endl; 
}


//prosedur algoritma bubble_sort secara ascending
void bubble_sort_Raket_Asc(anggota arr[], int n)
{
	for(int i = 0; i < 48; i++)
    {
		for(int j = 0; j < 48; j++)
        {
			if(arr[j].ketersediaan > arr[j+1].ketersediaan && arr[j].ketersediaan != 0 && arr[j+1].ketersediaan != 0)
            {
				swap(arr[j], arr[j+1]);
            }			
		}

                // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }

        //data ketersediaan raket berhasil disorting dengan menggunakan algoritma bubble sort 
        cout<<"bubble sort selesai !"<<endl;
}


//prosedur algoritma bubble_sort secara descending
void bubble_sort_Raket_Desc(anggota arr[])
{
	for(int i = 0; i < 48; i++){
		for(int j = 0; j < 48; j++){
			if(arr[j].ketersediaan < arr[j+1].ketersediaan &&
			(arr[j].ketersediaan != 0 && arr[j+1].ketersediaan != 0))
            {
				swap(arr[j], arr[j+1]);
            }			
		}

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }
        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }

    //data ketersediaan raket berhasil disorting dengan menggunakan algoritma bubble sort 
    cout<<"bubble sort selesai !"<<endl; 
}


//prosedur algoritma selection_sort secara ascending
void selection_sort_Umur_Asc(anggota arr[], int n)
{
    for (i = 0; i < n-1; i++)
    {
        min_index = i;
        for (j = i+1; j < n; j++)
        if (arr[j].umur < arr[min_index].umur && arr[min_index].umur != 0 && arr[j].umur != 0)
        {
            min_index = j;
            swap(arr[min_index], arr[i]);
        }

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }

    //data umur berhasil disorting dengan menggunakan algoritma selection sort
    cout<<"selection sort selesai !"<<endl;
}

//prosedur algoritma selection_sort secara descending
void selection_sort_Umur_Desc(anggota arr[], int n)
{
    for (i = 0; i < n-1; i++)
    {
        min_index = i;
        for (j = i+1; j < n; j++)
        if (arr[j].umur > arr[min_index].umur && arr[min_index].umur != 0 && arr[j].umur != 0)
        {
            min_index = j;
            swap(arr[min_index], arr[i]);
        }

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }

    //data umur berhasil disorting dengan menggunakan algoritma selection sort
    cout<<"selection sort selesai !"<<endl;
}


//prosedur algoritma selection_sort secara ascending
void selection_sort_Raket_Asc(anggota arr[], int n)
{
    for (i = 0; i < n-1; i++)
    {
        min_index = i;
        for (j = i+1; j < n; j++)
        if (arr[j].ketersediaan < arr[min_index].ketersediaan && arr[min_index].ketersediaan != 0 && arr[j].ketersediaan != 0)
        {
            min_index = j;
            swap(arr[min_index], arr[i]);
        }

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }

    //data umur berhasil disorting dengan menggunakan algoritma selection sort
    cout<<"selection sort selesai !"<<endl;
}


//prosedur algoritma selection_sort secara descending
void selection_sort_Raket_Desc(anggota arr[], int n)
{
    for (i = 0; i < n-1; i++)
    {
        min_index = i;
        for (j = i+1; j < n; j++)
        if (arr[j].ketersediaan > arr[min_index].ketersediaan && arr[min_index].ketersediaan != 0 && arr[j].ketersediaan != 0)
        {
            min_index = j;
            swap(arr[min_index], arr[i]);
        }

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }

    //data umur berhasil disorting dengan menggunakan algoritma selection sort
    cout<<"selection sort selesai !"<<endl;
}


// prosedur algoritma insertion_sort secara ascending
void insertion_sort_Umur_Asc(anggota arr[], int n)
{
    for (i = 1; i < n; i++)
    {
        anggota key = arr[i];
        j = i-1;
        while (j <= 0 && arr[j].umur > key.umur)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }

    //data umur berhasil disorting dengan menggunakan algoritma insertion sort
    cout<<"insetion sort selesai!"<<endl; 
}


// prosedur algoritma insertion_sort secara descending
void insertion_sort_Umur_Desc(anggota arr[], int n)
{
    for (i = 1; i < n; i++)
    {
        anggota key = arr[i];
        j = i-1;
        while (j >= 0 && arr[j].umur < key.umur)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }
    //data umur berhasil disorting dengan menggunakan algoritma insertion sort
    cout<<"insertion sort selesai!"<<endl; 
}


// prosedur algoritma insertion_sort secara ascending
void insertion_sort_Raket_Asc(anggota arr[], int n, int tipe)
{
    for (i = 1; i < n; i++)
    {
        anggota key = arr[i];
        j = i-1;
        while (j <= 0 && arr[j].ketersediaan > key.ketersediaan)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }

    if (tipe == 1)
    //data ketersediaan raket berhasil disorting dengan menggunakan algoritma insertion sort
    cout<<"insertion sort selesai!"<<endl;
    else
    cout << endl;
}


// prosedur algoritma insertion_sort secara descending
void insertion_sort_Raket_Desc(anggota arr[], int n)
{
    for (i = 1; i < n; i++)
    {
        anggota key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j].ketersediaan < key.ketersediaan)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }

    //data ketersediaan raket berhasil disorting dengan menggunakan algoritma insertion sort
    cout<<"insetion sort selesai!"<<endl; 
}

// prosedur algoritma selection_sort untuk mengurutkan nama
void selectionSort(anggota arr[], int n) 
{
    for (i = 0; i < n-1; i++)
    {
        min_index = i;
        for (j = i+1; j < n; j++)
        if (arr[j].nama < arr[min_index].nama)
        {
            min_index = j;
            swap(arr[min_index], arr[i]);
        }

        // buka file untuk re-write
        myFile.open("data_anggota.csv", ios::out);
        if (myFile.fail())
        {   
            cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
            myFile.close();
        }

        // write ulang semua data
        for (int i=0; i<50; i++) 
        {
            if(arr[i].nama == "")
            {
                break;
            }

            else
            {
                myFile << arr[i].nama << "," << arr[i].kelamin << "," << arr[i].umur << "," << arr[i].ketersediaan << endl;
            }

        }
        myFile.close();
        break;
    }
    
}

// prosedur algoritma binary search untuk mencari nama anggota
void binarySearch(anggota arr[], int low, int high)
{
    // buka file
    myFile.open("data_anggota.csv", ios::in);
    if (myFile.fail())
    {   
        cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
        myFile.close();
    }

    system("color 5A");
    // input nama yang ingin dicari
    string x;
    cout << "Masukkan nama yang ingin dicari : ";getline(cin, x);fflush(stdin);
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid].nama == x)
        {
            cout <<"\n===================================================== Data Ditemukan ===============================================================" << endl;
            cout<<"\n==================================================== Menampilkan Data ==============================================================\n\n";
            cout<<"====================================================================================================================================\n";
            cout<<"||"<<setw(25)<<"Nama Panggilan"<<setw(15)<<"||"<<setw(25)<<"Jenis Kelamin"<<setw(15)<<"||"<<setw(10)<<"Umur"<<setw(10)<<"||"<<setw(20)<<"Ketersediaan"<<setw(10)<<"||";
            cout<<"\n====================================================================================================================================";
 
            cout<<"\n||"<<setw(25)<<data_anggota[mid].nama<<setw(15)<<"||";
            cout<<setw(20)<<data_anggota[mid].kelamin<<setw(20)<<"||";
            cout<<setw(10)<<data_anggota[mid].umur<<setw(10)<<"||";
            cout<<setw(15)<<data_anggota[mid].ketersediaan<<setw(15)<<"||";
            cout<<"\n====================================================================================================================================";
        
            break;
        }
        else if (arr[mid].nama < x)
            low = mid + 1;
        else
            high = mid - 1;
    }
}

// prosedur algoritma interpolation search untuk mencari ketersediaan raket anggota
void interpolation_search(anggota arr[], int jumlahData)
{
    // buka file
    myFile.open("data_anggota.csv", ios::in);
    if (myFile.fail())
    {   
        cout << "\n\t\t\t\t\t\tMaaf, file tidak dapat dibuka / tidak ditemukan\n";
        myFile.close();
    }

    // inisiasi nilai variabel indeks
    int i_awal = 0, i_posisi;
    int i_akhir = jumlahData - 1;

    // input nilai yang ingin dicari
    int key;
    cout << "Masukkan ketersediaan raket anggota yang ingin dicari : ";
    cin >> key;

    while (true)
    {
        // rumus interpolation search
        i_posisi = (i_awal + ((key - arr[i_awal].ketersediaan) * (i_akhir - i_awal)) / (arr[i_akhir].ketersediaan + arr[i_awal].ketersediaan));

        // proses pembandingan search
        if (arr[i_posisi].ketersediaan == key)
        {
            cout <<"\n===================================================== Data Ditemukan ===============================================================" << endl;
            cout<<"\n==================================================== Menampilkan Data ==============================================================\n\n";
            cout<<"====================================================================================================================================\n";
            cout<<"||"<<setw(25)<<"Nama Panggilan"<<setw(15)<<"||"<<setw(25)<<"Jenis Kelamin"<<setw(15)<<"||"<<setw(10)<<"Umur"<<setw(10)<<"||"<<setw(20)<<"Ketersediaan"<<setw(10)<<"||";
            cout<<"\n====================================================================================================================================";
 

            cout<<"\n||"<<setw(25)<<data_anggota[i_posisi].nama<<setw(15)<<"||";
            cout<<setw(20)<<data_anggota[i_posisi].kelamin<<setw(20)<<"||";
            cout<<setw(10)<<data_anggota[i_posisi].umur<<setw(10)<<"||";
            cout<<setw(15)<<data_anggota[i_posisi].ketersediaan<<setw(15)<<"||";
            cout<<"\n====================================================================================================================================";
            
            break;
        }
        else if ((arr[i_posisi].ketersediaan < key) && (arr[i_posisi].ketersediaan >= arr[i_awal].ketersediaan))
        {
            i_awal = i_posisi + 1;
            continue;
        }
        else if ((arr[i_posisi].ketersediaan > key) && (arr[i_posisi].ketersediaan <= arr[i_akhir].ketersediaan))
        {
            i_akhir = i_posisi - 1;
            continue;
        }
        else
        {
            cout << "Anggota tidak ditemukan" << endl;
            break;
        }

    }
}

//prosedur untuk memilih urutan sorting secara ascending atau descending
void urutan()
{
    sorting:
    cout<<"\n==================================== SORTING DATA ANGGOTA ====================================";
    cout<<"\n================================== PILIHAN URUTAN SORTING ===================================\n";
    cout<<"1. Urutkan berdasarkan Ascending  : "<< endl;
    cout<<"2. Urutkan berdasarkan Descending : \n"<< endl;
    cout<<"0. Exit : "<< endl;
    urut = getch();
    switch(urut)
    {
        case '1':{system("cls");tampilan_sorting_Asc();break;}
        case '2':{system("cls");tampilan_sorting_Desc();break;}
        case '0':{break;}

        default:{cout<<"Pilihan yang anda masukkan salah, Mohon pilih kembali";getch();goto sorting;}
    }
}

//prosedur untuk tampilan sorting dengan urutan secara asceding
void tampilan_sorting_Asc()
{
    sortingg:
    cout<<"\n================================ SORTING DATA ANGGOTA ================================";
    cout<<"\n================================== PILIHAN SORTING ===================================\n";
    cout<<"1. Bubble Sort    (Mengurutkan umur anggota)"<< endl;
    cout<<"2. Insertion Sort (Mengurutkan umur anggota)"<< endl;   
    cout<<"3. Selection Sort (Mengurutkan umur anggota)\n"<< endl;
    cout<<"4. Bubble Sort    (Mengurutkan ketersediaan raket anggota)"<< endl;
    cout<<"5. Insertion Sort (Mengurutkan ketersediaan raket anggota)"<< endl;
    cout<<"6. Selection Sort (Mengurutkan ketersediaan raket anggota)\n"<< endl;   
    cout<<"0. Exit"<<endl;
    cout<<"Masukan Pilihan anda : ";
    pilih = getch();
    switch (pilih)
    {
        case'1':{system("cls");bubble_sort_Umur_Asc(data_anggota);goto sortingg;}
        case'2':{system("cls");insertion_sort_Umur_Asc(data_anggota, m);goto sortingg;}
        case'3':{system("cls");selection_sort_Umur_Asc(data_anggota, m);goto sortingg;}
        case'4':{system("cls");bubble_sort_Raket_Asc(data_anggota, 1);goto sortingg;}
        case'5':{system("cls");insertion_sort_Raket_Asc(data_anggota, m, 1);goto sortingg;}
        case'6':{system("cls");selection_sort_Raket_Asc(data_anggota, m);goto sortingg;}
        case'0':{break;}

        default:{cout<<"Pilihan yang anda masukkan salah, Mohon pilih kembali";getch();goto sortingg;}
    }
}

//prosedur untuk tampilan sorting dengan urutan secara desceding
void tampilan_sorting_Desc()
{
    sortingg:
    cout<<"\n================================ SORTING DATA ANGGOTA ================================";
    cout<<"\n================================== PILIHAN SORTING ===================================\n";
    cout<<"1. Bubble Sort    (Mengurutkan umur anggota)"<< endl;
    cout<<"2. Insertion Sort (Mengurutkan umur anggota)"<< endl;   
    cout<<"3. Selection Sort (Mengurutkan umur anggota)\n"<< endl;
    cout<<"4. Bubble Sort    (Mengurutkan ketersediaan raket anggota)"<< endl;
    cout<<"5. Insertion Sort (Mengurutkan ketersediaan raket anggota)"<< endl;
    cout<<"6. Selection Sort (Mengurutkan ketersediaan raket anggota)\n"<< endl;
    cout<<"0. Exit"<<endl;
    cout<<"Masukan Pilihan anda : ";
    pilih = getch();
    switch (pilih)
    {
        case'1':{system("cls");bubble_sort_Umur_Desc(data_anggota);goto sortingg;}
        case'2':{system("cls");insertion_sort_Umur_Desc(data_anggota, m);goto sortingg;}
        case'3':{system("cls");selection_sort_Umur_Desc(data_anggota, m);goto sortingg;}
        case'4':{system("cls");bubble_sort_Raket_Desc(data_anggota);goto sortingg;}
        case'5':{system("cls");insertion_sort_Raket_Desc(data_anggota, m);goto sortingg;}
        case'6':{system("cls");selection_sort_Raket_Desc(data_anggota, m);goto sortingg;}
        case'0':{break;}

        default:{cout<<"Pilihan yang anda masukkan salah, Mohon pilih kembali";getch();goto sortingg;}
    }
}

//prosedur untuk memilih searching secara nama atau ketersediaan raket
void tampilan_searching()
{
    searching:
    system("cls");
    cout<<"\n==================================== SEARCHING DATA ANGGOTA ====================================";
    cout<<"\n====================================== PILIHAN SEARCHING =======================================\n";
    cout<<"1. Cari berdasarkan nama  : "<< endl;
    cout<<"2. Cari berdasarkan ketersediaan raket : \n"<< endl;
    cout<<"0. Exit : "<< endl;
    urut = getch();
    switch(urut)
    {
        case '1':{system("cls");selectionSort(data_anggota, m);binarySearch(data_anggota, 0, m);getch();goto searching;}
        case '2':{system("cls");insertion_sort_Raket_Asc(data_anggota, m, 2);interpolation_search(data_anggota,m);getch();goto searching;}
        case '0':{break;}

        default:{cout<<"Pilihan yang anda masukkan salah, Mohon pilih kembali";getch();goto searching;}
    }
}
