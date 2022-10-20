#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>

#define REDC "\e[31m"
#define OFFC "\e[0m"

static void
usage(const char *pName)
{
    puts("Password entropy calculator\n");
    printf("Usage: %s <n> <l>\n\n", pName);
    puts("n:\tnumber of unique characters");
    puts("l:\tlength of password");
    puts("");
    printf("MPFR library: %-12s\nMPFR header:  %s (based on %d.%d.%d)\n",
            mpfr_get_version (), MPFR_VERSION_STRING, MPFR_VERSION_MAJOR,
            MPFR_VERSION_MINOR, MPFR_VERSION_PATCHLEVEL);
    printf("MPFR_PREC_MIN=%d and MPFR_PREC_MAX=%ld\n", MPFR_PREC_MIN,MPFR_PREC_MAX);
}

// You can calculate password entropy by log2( n ** l )
int main(int argc, char *argv[])
{
    mpfr_set_default_prec(1024);

    // declare and initialize variables
    mpfr_t n, l, powValue, log2Result;
    mpfr_init(n);
    mpfr_init(l);
    mpfr_init(powValue);
    mpfr_init(log2Result);


    if (argc != 3) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    int r;
    char *ep=NULL;
    if ((r=mpfr_strtofr(n, argv[1], &ep, 10, MPFR_RNDN)) != 0) {
        fprintf(stderr, REDC "Problem setting n=%s (returned %d)\n" OFFC, argv[1], r);
        return EXIT_FAILURE;
    }

    if ((r=mpfr_strtofr(l, argv[2], &ep, 10, MPFR_RNDN)) != 0) {
        fprintf(stderr, REDC "Problem setting l=%s (returned %d)\n" OFFC, argv[2], r);
        return EXIT_FAILURE;
    }


    if ((r=mpfr_pow(powValue, n, l, MPFR_RNDN)) != 0) {
        mpfr_fprintf(stderr, REDC "mpfr_pow(powValue, %.0RNf, %.0RNf, MPFR_RNDN) returned %d\n" OFFC, n, l, r);
        return EXIT_FAILURE;
    }

    mpfr_log2(log2Result, powValue, MPFR_RNDN);
    mpfr_printf( "password entropy for n=%.0RNf l=%.0RNf is %.RNf\n", n, l, log2Result);

    return EXIT_SUCCESS;
}
