// Existe um problema com esse código: estamos limitados pelos caracteres descritos
int conversorC(char caractere)
{
    switch (caractere)
    {
    case 'a':
        return 0;
        break;
    case 'b':
        return 1;
        break;
    case 'c':
        return 2;
        break;
    case 'd':
        return 3;
        break;
    case 'e':
        return 4;
        break;
    case 'f':
        return 5;
        break;
    case 'g':
        return 6;
        break;
    case 'h':
        return 7;
        break;
    }
}

char desconversorC(int caractere)
{
    switch (caractere)
    {
    case 0:
        return 'a';
        break;
    case 1:
        return 'b';
        break;
    case 2:
        return 'c';
        break;
    case 3:
        return 'd';
        break;
    case 4:
        return 'e';
        break;
    case 5:
        return 'f';
        break;
    case 6:
        return 'g';
        break;
    case 7:
        return 'h';
        break;
    }
}

// Existe um problema com esse código: que seria o caso em que a duas string tivessem a mesma soma
int conversorS(char *str)
{
    int soma = 0;
    strlen(str);

    for (int i = 0; i < strlen(str); i++)
        soma += str[i];

    switch (soma)
    {
    case 1217:
        return 0;
        break;
    case 550:
        return 1;
        break;
    case 423:
        return 2;
        break;
    case 554:
        return 3;
        break;
    case 322:
        return 4;
        break;
    case 626:
        return 5;
        break;
    case 547:
        return 6;
        break;
    case 546:
        return 7;
        break;
    case 535:
        return 8;
        break;
    }
}

char *desconversorS(int str)
{
    switch (str)
    {
    case 0:
        return "undershorts";
        break;
    case 1:
        return "pants";
        break;
    case 2:
        return "belt";
        break;
    case 3:
        return "shirt";
        break;
    case 4:
        return "tie";
        break;
    case 5:
        return "jacket";
        break;
    case 6:
        return "socks";
        break;
    case 7:
        return "shoes";
        break;
    case 8:
        return "watch";
        break;
    }
}