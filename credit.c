#include <stdio.h>
#include <cs50.h>

int check_Validity(long long int);
void detect_Card(long long int);
int get_length(long long int);

int main(void)
{
    long long n;
    do
    {
        n = get_long("Number : ") ;
    }
    while( n < 0 ) ;
    if ( check_Validity(n) == 1 )
        detect_Card(n);
    else
        printf("INVALID\n");        
}

int check_Validity(long long int n)
{
    long long int temp=n ;
    int ans=0 ;
    while( temp > 0 )
    {
        ans += temp%10 ;
        temp /= 100 ;
    }
    temp = n/10 ;
    while( temp > 0 )
    {
        if ( temp%10 > 4 )
            ans += (temp*2)%10 + 1;
        else
            ans += (temp%10)*2 ;
        temp /= 100;
    }
    if ( ans%10 == 0 )
        return 1;
    else
        return 0;
}

void detect_Card(long long int n )
{
    int l = get_length(n);
    int d = n/1000000000000; // d = n / (10^13)
    if ( l == 13 && d == 4 )
        printf("VISA\n");
    else if ( l == 15 && (d/10 == 34 || d/10 == 37) )
        printf("AMEX\n");
    else if ( l == 16 && d/100 >50 && d/100 < 56 )
        printf("MASTERCARD\n");
    else if ( l == 16 && d/1000 == 4 )
        printf("VISA\n");
    else
        printf("INVALID\n");
}

int get_length( long long int n )
{
    int count = 0 ;
    while( n > 0 )
    {
        count++;
        n /= 10;
    }
    return count;
}
