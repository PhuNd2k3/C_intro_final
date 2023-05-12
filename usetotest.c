#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
typedef struct{
    char code[50];
    double l,w,h,m;
    int type;
}buucuc;

void input(buucuc hang[],int n){
    int stop=1;
    for(int i=0;i<n;i++){
        do{
        printf("Nhap ma kien hang thu %d: ",i+1);
        fflush(stdin);
        gets(hang[i].code);
        for(int j=0;j<strlen(hang[i].code);j++){
            if (isalpha(hang[i].code[j])==0 && isdigit(hang[i].code[j])==0) {
                stop=0;
                printf("Nhap sai ma kien hang\n");
                break;
            }
            else {
                stop=1;
            }
        }
        }while (stop==0);
        do{
            if(strlen(hang[i].code)<8||strlen(hang[i].code)>20){
                printf("Nhap sai kich thuoc\n");
                printf("Nhap lai ma kien hang: ");
                fflush(stdin);
                gets(hang[i].code);
            } 
        }while (strlen(hang[i].code)<8||strlen(hang[i].code)>20);

        
        
        printf("Nhap chieu dai: ");
        scanf("%lf",&hang[i].l);
        printf("Nhap chieu rong: ");
        scanf("%lf",&hang[i].w);
        printf("Nhap chieu cao: ");
        scanf("%lf",&hang[i].h);
        printf("Nhap trong luong tinh: ");
        scanf("%lf",&hang[i].m);
        printf("Nhap hinh thuc van chuyen: ");
        scanf("%d",&hang[i].type);
    }
}
void check(buucuc hang[],int n,int mark[]){
    for(int i=0;i<n;i++){
        if (hang[i].h<10||hang[i].w<10||hang[i].l<10)
        mark[i]=1;
        else if(hang[i].h>150||hang[i].w>150||hang[i].l>150)
        mark[i]=2;
        else if(hang[i].m>30)
        mark[i]=3;
        else mark[i]=0;
    }
}
void tuchoi(buucuc hang[],int n,int mark[]){
    int sign=0;
    printf("Chi tiet kien hang bi tu choi\n===================\n");
    printf("%-20s%s\n","Ma kien hang","Ly do tu choi");
    for (int i=0;i<n;i++){   
        switch (mark[i])
        {
        case 1:
            printf("%-20s%s\n",hang[i].code,"ER1");
            sign=1;
            break;
        case 2:
            printf("%-20s%s\n",hang[i].code,"ER2");
            sign=1;
            break;
        case 3:
            printf("%-20s%s\n",hang[i].code,"ER3");
            sign=1;
            break;
        }
    }
    if(sign==0) printf("Khong co kien hang nao bi tu choi!!\n");
}

double chuanhoa(double m_quydoi){
    double x;
    x=m_quydoi-floor(m_quydoi);
    if(x>0&&x<0.5) m_quydoi=floor(m_quydoi)+0.5;
    else if(x>0.5) m_quydoi=floor(m_quydoi)+1;
    return m_quydoi;
}

void quydoi(buucuc hang[],int n,int mark[],double m_quydoi[]){
    double max;
    for(int i=0;i<n;i++){
        if(mark[i]==0){
            if((hang[i].h+hang[i].w+hang[i].l)<80){
            m_quydoi[i]=hang[i].m;
            m_quydoi[i]=chuanhoa(m_quydoi[i]);
            }
            else {
                if(hang[i].type==1){
                    max=hang[i].l*hang[i].h*hang[i].w/6000;
                    m_quydoi[i]=max>hang[i].m?max:hang[i].m;
                    m_quydoi[i]=chuanhoa(m_quydoi[i]);
                }
                else {
                    max=hang[i].l*hang[i].h*hang[i].w/4000;
                    m_quydoi[i]=max>hang[i].m ? max : hang[i].m;
                    m_quydoi[i]=chuanhoa(m_quydoi[i]);
                }
        }
    }
}
}

void tinhtien(buucuc hang[],int n,int mark[],double m_quydoi[],int cuocphi[]){
    for(int i=0;i<n;i++){
        if(mark[i]==0){
            if(m_quydoi[i]<=3){
                if(hang[i].type==0)
                cuocphi[i]=16500;
                else cuocphi[i]=22000;
            }
            else{
                if(hang[i].type==0){
                    cuocphi[i]=16500+((m_quydoi[i]-3)/0.5*2500);
                }
                else    cuocphi[i]=22000+((m_quydoi[i]-3)/0.5*2500);
            }
        }
    }
}

void exe5(buucuc hang[],int n,int mark[],double m_quydoi[],int cuocphi[]){
    int count=0;
    printf("Chi tiet kien hang hop le\n===================\n");
    printf("%-20s%-30s%-30s%-15s\n","Ma kien","Can nang tinh phi","Hinh thuc van chuyen","cuoc phi");
    for(int i=0;i<n;i++){
        if(mark[i]==0){
            if(hang[i].type==0){
                //printf("%-20s%-30.2lf%-30s%d\n",hang[i].code,m_quydoi[i],"Chuyen thuong",cuocphi[i]);
                printf("%-20s%-30.2lf%-30s%d\n",hang[i].code,m_quydoi[i],"Chuyen thuong",cuocphi[i]);
                count++;
            }
            else {
                printf("%-20s%-30.2lf%-30s%d\n",hang[i].code,m_quydoi[i],"Chuyen Nhanh",cuocphi[i]);
                //printf("BOO\n");
                count++;
            }
        }
    }
    printf("Tong so: %d\n",count);
}

void traphi(buucuc hang[],int n,int mark[],int cuocphi[]){
    long int tong=0;
    int count=0;
    for(int i=0;i<n;i++){
        if(mark[i]==0){
            count++;
            tong=tong+cuocphi[i];
        }
    }
    double VAT=tong*8/100;
    double tongchi=tong+VAT;
    printf("Chi phi van chuyen\n================\n");
    printf("So luong kien hang da nhan: %d\n",count);
    printf("Tong tien cuoc: %d\n",tong);
    printf("VAT: %.0lf\n",VAT);
    printf("Tong chi phi : %.0lf\n",tongchi);
}

int main(){
    int stop=0;
    int choose;
    //struct
    buucuc hang[100];
    int n;
    //menu
    int mark[100];
    double m_quydoi[100];
    int cuocphi[100];
    do{
        printf("Moi ban chon chuc nang\n========================\n");
        printf("1. Nhap thong tin kien hang\n");
        printf("2. Chi tiet cac kien hang bi tu choi\n");
        printf("3. Chi tiet cac kien hang hop le\n");
        printf("4. Tinh phi van chuyen\n");
        printf("5. Exit\n");
        scanf("%d",&choose);
        switch (choose)
        {
        case 1:
            do{
                printf("Nhap vao so luong kien hang: ");
                scanf("%d",&n);
                if(n>200||n<1) printf("Nhap so luong kien hang trong khoang 1 den 200");
            }while (n>200||n<1);
            input(hang,n);
            break;
        case 2:
            check(hang,n,mark);
            tuchoi(hang,n,mark);
            quydoi(hang,n,mark,m_quydoi);
            tinhtien(hang,n,mark,m_quydoi,cuocphi);
            break;
        case 3:
            exe5(hang,n,mark,m_quydoi,cuocphi);
            break;
        case 4:
            traphi(hang,n,mark,cuocphi);
            break;
        case 5:
            stop=1;
            printf("Ket thuc chuong trinh!!");
            break;
        }
    }while(stop!=1);
    return 0;
}
