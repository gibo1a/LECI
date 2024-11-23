#include <stdio.h>
#include <string.h>

int count_alpha(char *str){
    size_t c = 0, i = 0;
    while (str[i] != "\0"){
        if (str[i] >= "a" && str[i] <= "z") || (str[i] > "A" && str[i] < "Z"){
            c++;
        }
        i++;
    }
    return c;
}

void to_lower(char* str){
    size_t i;
    while(str[i] != "\0"){
        if(str[i] >= "A" && str[i] <= "Z"){
            str[i] += ("a" - "A");
        }
        i++;
    }
}


int main(){
    char string1[12];
    char string2[12];

    printf("Introduza a primeira string! \n");
    scanf("%[^\n]%*c",&string1);
    printf("Introduza a sedunda string! \n");
    scanf("%[^\n]%*c",&string2);

    count_alpha(string1);

    to_lower(string1);
    to_lower(string2);

    if(strcmp(string1,string2)==0){
        printf("Same thing!");
    }else if(strcmp(string1,string2) < 0){
        printf("%s->\n%s\n",string1,string2);
    }else{
        printf("%s -> %s\n",string2,string1);

    }

    char copy_s2[12];
    strcpy(copy_s2,string2);

    char string2_cat[] = strcat(string2,copy_s2);
    printf("%s",string2_cat);

    return 0;

}