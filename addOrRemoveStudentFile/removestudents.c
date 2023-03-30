#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
//Burak Önce 20120205052
//Bu program Metin belgesinde silinmesini istediğiniz numaralı öğreniyi siler

struct student{
//struct atamaları girilecek bilgiler için tanımlanır
char id[10];

char name[40];

char surname[40];

struct student *next;

} head = {"ID", "NAME", }; //Başlangıç için bir struck ticki belirlenir

int read_students (FILE *f){ 

if (f == NULL) return -1;

struct student *temp = &head;

char l[50]; 

while(fgets(l, 50, f) != NULL){

temp->next = (struct student *) malloc(sizeof(struct student)); //hafıza sıkıntısı yaşanmaması için yer açılır

//pointır atamaları yapılır
char *id = strtok(l, "\t");   

char *name = strtok(NULL, "\t");

char *surname = strtok(NULL, "\t");

if (id != NULL && name != NULL){

//programcıya sıkıntı çıkarmaması için strncpy kullanılır
strncpy(temp->next->id, id,10);

strncpy(temp->next->name, name, 40);

strncpy(temp->next->surname, surname, 40);

temp = temp->next; 
}
}
//tempin gösterdiği değerin nextini eski haline getiririrz
temp->next = NULL;

return 0;
}

int sil(FILE *f, char *no){

FILE *f2;
//dosya yoksa oluşturulur
f2=fopen("ogrenci.txt","w");


struct student *temp = &head;
temp = temp->next;
while(temp != NULL){
//dosya atamaları yapılır

if(strcmp(temp->id,no)){ //eğer ki scanf ile alınan sayı temp->id ye eşit ise yeni belgeye o satır yazılmaz böylelikle istenilen no lu öğrencii blgisi silinmiş olur
fputs(temp->id, f2);
fputs("\t", f2);
}
if(strcmp(temp->id,no)){   // aynı şekilde
fputs(temp->name, f2);
fputs("\t", f2);
}
if(strcmp(temp->id,no)){  // aynı şekilde
fputs(temp->surname, f2);
}
temp = temp->next;
}
fclose(f2);
return 0;
}

int main(){
char *no;
printf("Silinmesini istediginiz ogrencinin numarasini giriniz : ");
scanf("%s",no);
FILE *f = fopen("students.txt", "r"); 
read_students(f);

sil(f,no);
remove("students.txt"); //eski dosya silinir
rename("ogrenci.txt","students.txt"); //yeni dosya adı değiştirilir

fclose(f);
return 0;
}