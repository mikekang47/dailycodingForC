//
//
//  파일명 : BlackJack.c
//  프로그램 개요 : 두명의 플레이어를 이름과, 잔고, 배팅값을 입력받고 딜러와의 게임에서 승패를 결정하는 프로그램
//
//  열거형과 구조체를 활용하고 이를 통해서 패를 출력한다
//  카드덱 구성은 filldeck, shuffle는 카드 섞기, deal은 카드 분배
//  compare를 이용해서 딜러와의 승패 비교후 잔고 수정 및 출력
//
//
//  입력 : 두 선수의 이름 및 잔고 배팅값
//  출력 : 각 선수의 승패 및 잔고
//
//
//  날짜 : 2020년 12월 6일
//  버전 : 1.0
//  작성자 : 중국어문학과 강경록
//
//
//
//딜러는 17이하이면 무조건 한장 떠 뽑고, 17이상 21미만이면 히트하지 않는다.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

enum enumsuit {Hearts, Diamonds, Clubs, Spades}; //열거형으로 모양 정의
enum enumface {Ace, Deuce, Three, Four, Five, Six, Seven,Eight, Nine, Ten, Jack, Queen, King };//열거형으로 숫자 정의
typedef enum enumsuit enumsuit;//typdef로 재정의
typedef enum enumface enumface;//typdef로 재정의
struct card {   //구조체 card선언
    enumsuit suit;//suit를 맴버로 선언
    enumface face;//face를 맴버로 선언
};
typedef struct card card;//typdef로 재정의
card deck[52];//52장의 덱 구성

struct person{ //구조체 person선언
    char p1[100];//사람1
    char p2[100];//사람2
    char dealer[100];//딜러
};
struct person people = {};//참가자를 공백 구조체로 정의한 후 입력받음
void player(void)
{
    printf("블랙잭 게임의 참여자 2명을 차레로 입력하시오\n");
    printf("player1: ");
    scanf("%s", people.p1);
    printf("player2: ");
    scanf("%s", people.p2);
}

/*배팅머니를 담을 구조체 선언*/
struct battingmoney //배팅머니를 담을 구조체 선언
{
    int p1money;
    int p2money;
};
struct battingmoney money = {0, 0};


/*카드 합을 담을 구조체 선언*/
struct point
{
    int p1;
    int p2;
    int p1_1;
    int p2_1;
    int dealer;
};
struct point pp = {0, 0, 0, 0, 0};

/* 잔고를 담을 구조체와 구조체 변수*/
struct balance
{
    int b1;
    int b2;
};

struct balance bb = {0, 0};


/*카드의 숫자 정보와 모양 정보를 담은 이차원 배열 선언*/
char *strface[] = {"A", "2", "3", "4", "5", "6", "7","8", "9", "10", "J", "Q", "K"};//전역변수로 숫자를 이차원 배열에 정의
char *strsuit[] = {"♥","♦", "♣", "♠"};//전역변수로 모양을 이차원 배열에 정의

/*52장의 카드를 4가지의 무늬로 분류*/
void filldeck(card *deck) //무늬와 숫자로 카드덱 구성
{
    for (int i = 0; i <= 51; i++ ) //52장의 카드 구성
    {
        deck[i].face = i % 13; //숫자가 13가지 존재
        deck[i].suit = i / 13;
    }
}

/*카드를 섞는 함수 */
void shuffle(card *deck)
{
    card temp;
    srand((unsigned int)time(NULL));  //실행할때마다 다른 모양, 다른 숫자를 나타내기 위해서
    for(int i = 0; i <= 51; i++) //카드 개수만큼 반복
    {
        int j = rand() % 52; //아래는 변수 교환
        temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

/*카드를 섞는 애니메이션*/
void shuffleanimation()
{
    printf("카드를 섞습니다.\n");
    sleep(1.3);
    printf("             ______  _____  _____\n");
    printf("            /     / /    / /    /\n");
    printf("           /   * / /  * / /  * /\n");
    printf("          /   * / /  * / /  * /\n");
    printf("         /     / /    / /    /  \n");
    printf("         -----  ------ -----\n");
    sleep(1.3);
    printf("      ____        _______     --- \n");
    printf("           ---    \\______\\      -----\n");
    printf("     ----        ///     /    ----\n");
    printf("    ----   --   ///  *  / ___    -----\n");
    printf("   ----   ___  ///  *  /    ---\n");
    printf("      -----   ///_____/        ----\n\n\n");
    sleep(1.3);
}

int ablackjack;//첫번째 플레이어가 블랙잭인지 검사
int bblackjack;//두번째 플레이어가 블랙잭인지 검사
/* 카드를 분배하는 함수 */
void deal(card *deck, int t, int k);
int adoubledown = 0; //첫번째 플레이어가 더블을 했는지 검사
int bdoubledown = 0; //두번째 플레이어가 더블을 했는지 검사


/*인슈어런스를 사용했는지 여부를 저장하는 변수*/
int insurance;
int ainsurance= 0;
int binsurance = 0;

/* 인슈어런스 여부를 물어보는 함수*/
void askinsurance()
{
    printf("\n%s 님 insurane? (y : 1/n : 0) >> ", people.p1);
    scanf("%d", &insurance);
    /* 인슈어런스에 동의를 하면 배팅금액의 절반을 지불한다.*/
    if(insurance == 1)
    {
        printf("배팅금액의 절반을 지불합니다.\n");
        bb.b1 -= money.p1money / 2;
        ainsurance++;
    }
    printf("\n%s 님 insurane? (y : 1/n : 0) >> ", people.p2);
    scanf("%d", &insurance);
    if(insurance == 1)
    {
        printf("배팅금액의 절반을 지불합니다.\n");
        bb.b2 -= money.p2money / 2;
        binsurance++;
    }
}

/*딜러의 카드 분배*/
/*딜러의 패 인덱스는 16~20까지 총 네장 할당 받을 수 있도록 정의했다.*/
int dealerblackjack = 0;
void dealerdeal(card *deck)
{
    pp.dealer = 0;
    for(int i = 16; i < 20; i++)
    {
        /* 두번째 카드는 히든카드여야 하기 때문에 *로 표시하되 합은 저장한다.*/
        printf("%3s%-10s", i%17 == 0? "*" :strface[deck[i].face], i%17 == 0? "" : strsuit[deck[i].suit]);
        if(deck[i].face < 10) //인덱스가 10보다 작을때 즉, 숫자 10이하인 수가 나올경우 인덱스+1한 값을 딜러 점수에 더한다.
        {
            pp.dealer += deck[i].face + 1;//딜러점수에 더함
        }
        else if(deck[i].face >= 10)
        {
            pp.dealer += 10; //인덱스가 10이상인 경우는 J,Q,K이고, 이 숫자들은 모두 10으로 취급되기 때문에 10을 저장.
        }
        /* 처음 딜러 카드분배는 두장만 분배해야 하기 때문에, 두장이 분배가 되면 반복문을 종료시킨다.*/
        if(i == 17)
        {
            i = 20;
        }
    }
    /* 딜러의 첫번째 카드가 A이고 딜러 패 합산이 11보다 작으면 자동적으로 A를 11로 선택한다.*/
    if(pp.dealer <= 11 && (deck[16].face == 0))
    {
        pp.dealer += 10;
    }
    /* 인슈어런스에 관한 함수*/
    if(deck[16].face == 0)
    {
        askinsurance();
    }
    
    
    printf("\n");
}


/* 딜러가 마지막에 히든카드를 공개할때의 함수 */
void dealerOpendeal(card *deck, int a)
{
    pp.dealer = 0;
    for(int i = 16; i < 20; i++)
    {
        printf("%3s%-10s", strface[deck[i].face], strsuit[deck[i].suit]);
        if(deck[i].face < 10)
        {
            pp.dealer += deck[i].face + 1;
        }
        else if(deck[i].face >= 10)
        {
            pp.dealer += 10;
        }
        if(pp.dealer == 21 && i < 18)//딜러가 블랙잭이면 블랙잭 변수를 1 증가시킨다.
        {
            dealerblackjack++;
            printf("\nDealer BlakJack!\n");
        }
        if(i == a + 15 || a > 4)
        {
            i = 20;
        }
    
    }
    printf("\n");
}



/*처음에 잔고를 입력받음*/
void checkbalance(void)
{
    while(1)//실패하면 계속 진행하도록 무한루프를 구성함
    {
        int n, m;
        printf("선수 두명의 잔고를 차례로 입력하시오\n");
        printf("player1 >> ");
        n = scanf("%d", &bb.b1);
        printf("player2 >> ");
        m = scanf("%d", &bb.b2);
        if(n == 1 && m == 1)
        {
            printf("입력이 완료되었습니다.\n");
            break;
        }
        else if(bb.b1 < 1000 || bb.b2 < 1000)
        {
            printf("입력이 제대로 이루어지지 않았습니다. 다시 시도하세요.\n");
            while(getchar() != '\n'); //버퍼를 비움으로써 무한루프 오류 방지
            continue;
        }
        else{
            printf("입력이 제대로 이루어지지 않았습니다. 다시 시도하세요.\n");
            while(getchar() != '\n'); //버퍼를 비움으로써 무한루프 오류 방지
            continue;
        }
    }
}

/*배팅을 금액을 결정하는 함수*/
/*배팅한 금액이 잔고보다 크면 오류를 발생하도록 설정하고, 그렇지 않을경우 진행*/
void batting(void)
{
    printf("배팅 최소금액은 1000원 입니다.\n1000원 이상을 입력해주세요.\n");
    sleep(1);
    printf("선수 두명의 배팅금액을 차례로 입력하시오 \n");
    while(1)
    {
        int n, m;
        printf("player1 >> ");
        n = scanf("%d", &money.p1money);
        printf("player2 >> ");
        m = scanf("%d", &money.p2money);
        if(money.p1money > bb.b1)
        {
            printf("배팅금액이 잔고보다 큽니다. 다시 입력해주세요\n");
            while(getchar() != '\n'); //버퍼 비움
            continue;
        }
        else if(money.p1money < 1000)
        {
            printf("배팅 최소금액보다 낮습니다. 다시 입력해주세요\n");
            while(getchar() != '\n'); //버퍼 비움
        }
        if(money.p2money > bb.b2)
        {
            printf("배팅금액이 잔고보다 큽니다. 다시 입력해주세요\n");
            while(getchar() != '\n'); //버퍼 비움
            continue;
        }
        else if(money.p2money < 1000)
        {
            printf("배팅금액이 잔고보다 큽니다. 다시 입력해주세요\n");
            while(getchar() != '\n'); //버퍼 비움
            continue;
        }
        if(n == 1 && m == 1)
        {
            printf("배팅이 완료되었습니다.\n");
            break;
        }
        else
        {
            printf("배팅이 제대로 이루어지지 않았습니다. 다시 시도하세요.\n");
            while(getchar() != '\n'); //버퍼 비움
            continue;
        }
    }
}

/* 플레이어의 점수가 21을 초과하면 Bust가 발생하기 때문에 bust발생여부를 int함수로 체크*/

int bustornot(int a)
{
    if(a > 21)
        return 1;
    else
        return 0;
}

/* push는 딜러와 플레이어가 같은 점수가 나왔다면 push */
void push(int a, char *b)
{
    if(a == pp.dealer)
    {
        printf("%s님 Push!\n", b);
    }
}

/* 가진 금액을 수정하고 승패를 결정하는 함수*/
/* 총 세가지의 경우로 나눠진다. dealer가 21을 초과했을때, 21보다 작을때, 21일때*/
/* 위의 세가지 경우에서 각각의 경우로 문제를 처리한다.*/
void compare()
{
    if(pp.dealer > 21)//21을 초과한경우
    {
        printf("딜러 busted!\n");//딜러가 Bust인것은 공통이며
        if(bustornot(pp.p1) == 0 || pp.p1 == 21) // 첫번째 플레이어가 21일 이하의 패를 가지고 있으면 돈을 딴다
        {
            bb.b1 = bb.b1 + money.p1money;
            printf("\n돈을 땄습니다!\n%s 님 현재 보유금액 %d원\n", people.p1, bb.b1);
        }
        else if(bustornot(pp.p1) == 1) // 첫번째 플레이어도 21을 초과하여 bust가 발생했으면 돈을 잃는다
        {
            bb.b1 = bb.b1 - money.p1money;
            printf("\n돈을 잃었습니다!\n%s 님 현재 보유금액 %d원\n", people.p1, bb.b1);
        }
        else if(pp.p1 == 21 && ablackjack == 1)//첫번째 플레이어가 21이면서 동시에 블랙잭이면 배팅한 금액의 1.5배를 얻는다.
        {
            bb.b1 = bb.b1 + money.p1money*1.5;
            printf("%s님 Black Jack!!\n%s 님 현재 보유금액 %d원\n", people.p1, people.p1, bb.b1);
        }
        /* 이하는 두번째 플레이어의 경우이기에 마찬가지이다. */
        if(bustornot(pp.p2) == 0 || pp.p2 == 21)
        {
            bb.b2 = bb.b2 + money.p2money;
            printf("\n돈을 땄습니다!\n%s 님 현재 보유금액 %d원\n", people.p2, bb.b2);
           
        }
        else if(bustornot(pp.p2) == 1)
        {
            bb.b2 = bb.b2 - money.p2money;
            printf("\n돈을 잃었습니다!\n%s 님 현재 보유금액 %d원\n", people.p2, bb.b2);
           
        }
        else if(pp.p2 == 21 && bblackjack == 1)
        {
            bb.b2 = bb.b2 + money.p2money*1.5;
            printf("%s님 Black Jack!!\n%s 님 현재 보유금액 %d원\n", people.p2, people.p2, bb.b2);
           
        }
    }
    /* 다음은 딜러가 21 미만인 경우, 즉 17이상 21미만인 경우이다.*/
    else if(pp.dealer < 21)
    {
        if((bustornot(pp.p1)) == 0) //첫번째 플레이어가 버스트가 나지 않았고
        {
            if(pp.dealer > pp.p1)// 딜러의 합이 더 크다면 플레이어가 진다
            {
                printf("\n%s 님 loose!\n", people.p1);
                bb.b1 = bb.b1 - money.p1money;
                printf("\n%s 님 현재 보유금액 %d원\n",people.p1, bb.b1);
            }
            else if(pp.dealer < pp.p1)//딜러의 합보다 플레이어의 합이 높다면 플레이어가 이긴다.
            {
                printf("\n%s 님 win!\n", people.p1);
                bb.b1 = bb.b1 + money.p1money;
                printf("\n%s 님 현재 보유금액 %d원\n",people.p1, bb.b1);
            }
            else if(pp.dealer == pp.p1)//딜러의 합과 플레이어의 합이 같다면 Push가 발생한다.
            {
                push(pp.p1, people.p1);
            }
        }
        else if(bustornot(pp.p1) == 1)//첫번째 플레이어가 Bust가 발생했다면 무조건 진다.
        {
            printf("\n%s 님 Busted!\n", people.p1);
            bb.b1 = bb.b1 - money.p1money;
            printf("\n%s 님 현재 보유금액 %d원\n",people.p1, bb.b1);
        }
        /* 이하는 두번재 플레이어의 경우이기에 첫번째 플레이어와 동일하다*/
        if((bustornot(pp.p2)) == 0)
        {
            if(pp.dealer > pp.p2)
            {
                printf("\n%s 님 loose!\n", people.p2);
                bb.b2 = bb.b2 - money.p2money;
                printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            }
            else if(pp.dealer < pp.p2)
            {
                printf("\n%s 님 win!\n", people.p2);
                bb.b2 = bb.b2 + money.p2money;
                printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            }
            else if(pp.dealer == pp.p2)
            {
                push(pp.p2, people.p2);
            }
        }
        else if(bustornot(pp.p2) == 1)
        {
            printf("\n%s 님 Busted!\n", people.p2);
            bb.b2 = bb.b2 - money.p2money;
            printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            
        }
    }
    /* 마자막 경우 딜러가 21이라면 */
    else if(pp.dealer == 21)
    {
        if(dealerblackjack != 0)//동시에 딜러가 블랙잭이라면
        {
            if(pp.p1 == 21 && ablackjack != 0)
            {
                push(pp.p1, people.p1);
                if(ainsurance == 1)
                {
                    printf("보험금액을 땄습니다.\n");
                    bb.b1 += money.p1money*2;
                }
                else
                    printf("보험금액을 잃었습니다.\n");
                printf("\n%s 님 현재 보유금액 %d원\n",people.p1, bb.b1);
            }
            else if(pp.p1 == 21 && ablackjack == 0)
            {
                printf("\n%s 님 loose!\n", people.p1);
                bb.b1 = bb.b1 - money.p1money;
                if(ainsurance == 1)
                {
                    printf("보험금액을 땄습니다.\n");
                    bb.b1 += money.p1money;
                }
                else
                    printf("보험금액을 잃었습니다.\n");
                printf("\n%s 님 현재 보유금액 %d원\n",people.p1, bb.b1);
            }
            if(pp.p2 == 21 && bblackjack != 0)
            {
                push(pp.p2, people.p2);
                if(binsurance == 1)
                {
                    printf("보험금액을 땄습니다.\n");
                    bb.b2 += money.p2money*2;
                }
                else
                    printf("보험금액을 잃었습니다.\n");
                printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            }
            else if(pp.p2 == 21 && bblackjack == 0)
            {
                printf("\n%s 님 loose!\n", people.p2);
                bb.b2 = bb.b2 - money.p2money;
                if(binsurance == 1)
                {
                    printf("보험금액을 땄습니다.\n");
                    bb.b2 += money.p2money*2;
                }
                else
                    printf("보험금액을 잃었습니다.\n");
                printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            }
        }
        //딜러의 합이 21이지만 블랙잭이 아니라면
        else if(dealerblackjack == 0)
        {
            if(pp.p1 == 21 && ablackjack != 0)//첫번째 플레이어가 블랙잭이면
            {
                printf("\n%s 님 win!\n", people.p1);
                if(ainsurance == 1)//보험을 했으면 보험금을 잃고 아니면 플레이어의 승리
                {
                    printf("보험금을 잃었습니다.\n");
                }
                bb.b1 = bb.b1 + money.p1money;
                printf("\n%s 님 현재 보유금액 %d원\n",people.p1, bb.b1);
            }
            else if(pp.p1 == 21 && ablackjack == 0)//첫번째 플레이어가 블랙잭이 아니면
            {
                push(pp.p1, people.p1);//푸쉬
                if(ainsurance == 1)//보험을 했으면 보험금을 잃는다.
                {
                    printf("보험금을 잃었습니다.\n");
                }
                printf("\n%s 님 현재 보유금액 %d원\n",people.p1, bb.b1);
            }
            else if(pp.p1 < 21)//첫번째 플레어가 21보다 작으면
            {
                printf("\n%s 님 loose!\n", people.p1);
                if(ainsurance == 1)//보험을 했으면 보험금을 잃는다.
                    printf("보험금을 잃었습니다.\n");
                bb.b1 = bb.b1 - money.p1money;
                printf("\n%s 님 현재 보유금액 %d원\n",people.p1, bb.b1);
            }
            else if(pp.p1 > 21)
            {
                printf("\n%s 님 Busted!\n", people.p1);
                bb.b1 = bb.b1 - money.p1money;
                if(ainsurance == 1)//보험을 했으면 보험금을 잃는다.
                {
                    printf("보험금을 잃었습니다.\n");
                }
                printf("\n%s 님 현재 보유금액 %d원\n",people.p1, bb.b1);
            }
            /* 아래는 두번째 플레이어의 경우로 첫번째 플레이어와 동일*/
            if(pp.p2 == 21 && bblackjack != 0)
            {
                printf("\n%s 님 win!\n", people.p2);
                if(binsurance == 1)
                {
                    printf("보험금을 잃었습니다.\n");
                }
                bb.b2 = bb.b2 + money.p2money;
                printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            }
            else if(pp.p2 == 21 && bblackjack == 0)
            {
                push(pp.p2, people.p2);
                if(binsurance == 1)
                {
                    printf("보험금을 잃었습니다.\n");
                }
                printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            }
            if(pp.p2 == 21 && bblackjack != 0)//두번째 플레이어가 블랙잭이면
            {
                printf("\n%s 님 win!\n", people.p2);
                if(binsurance == 1)//보험을 했으면 보험금을 잃고 아니면 플레이어의 승리
                {
                    printf("보험금을 잃었습니다.\n");
                }
                bb.b2 = bb.b2 + money.p2money;
                printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            }
            else if(pp.p2 == 21 && bblackjack == 0)//두번째 플레이어가 블랙잭이 아니면
            {
                push(pp.p2, people.p2);//푸쉬
                if(binsurance == 1)//보험을 했으면 보험금을 잃는다.
                {
                    printf("보험금을 잃었습니다.\n");
                }
                printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            }
            else if(pp.p2 < 21)//두번째 플레어가 21보다 작으면
            {
                printf("\n%s 님 loose!\n", people.p2);
                if(binsurance == 1)//보험을 했으면 보험금을 잃는다.
                    printf("보험금을 잃었습니다.\n");
                bb.b2 = bb.b2 - money.p2money;
                printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            }
            else if(pp.p2 > 21)
            {
                printf("\n%s 님 Busted!\n", people.p2);
                bb.b2 = bb.b2 - money.p2money;
                if(binsurance == 1)//보험을 했으면 보험금을 잃는다.
                {
                    printf("보험금을 잃었습니다.\n");
                }
                printf("\n%s 님 현재 보유금액 %d원\n",people.p2, bb.b2);
            }
        }
    }
}


void result(void);//현재의 점수를 출력하는 함수
void checkadoubledown(void);
void checkbdoubledown(void);
void checkPlayerBlackJack(void);

int main()
{
    player();//사람의 이름을 입력받음
    checkbalance();//잔고를 입력받음
    while(1)
    {
        int count = 0;//첫번째 플레이어가 히트를 몇번했는지 카운트 하는 변수
        int h = 0;//히트할지 말지를 선택하는 변수
        int go = 0;//계속할것인지 그만둘것인지 선택하는 변수
        adoubledown = 0;//오류를 방지하기 위해 모두 0으로 초기화
        bdoubledown = 0;
        batting();//루프 안에서 배팅을 구성했기 때문에 잔고가 초기화되지 않고 배팅만 초기화됨
        filldeck(deck);
        shuffle(deck);//카드를 섞음
        shuffleanimation(); //섞는 애니메이션
        sleep(1.3);
        printf("    %8s    \n", "dealer");
        dealerdeal(deck);//딜러의 카드를 먼저 분배
        sleep(1.3);
        printf("      %10s         %14s\n", people.p2 ,people.p1);
        deal(deck,2,2);//플레이어의 카드를 2장씩 분배한다.
        result();//총합을 출력
        /* 아래는 더블 다운의 경우 무조건 한장을 뽑도록 한다*/
        int i = 0;
        if(bdoubledown != 0 && adoubledown != 0)
        {
            printf("      %10s         %14s\n", people.p2 ,people.p1);
            deal(deck,3,3);
            if((deck[8].face == 0 || deck[9].face == 0) && pp.p1 > 21)//A가 포함되어 있는데 hit을 한후 21이 넘으면 A값을 1로 설정
                    pp.p1 -= 10;
            if((deck[0].face == 0 || deck[1].face == 0) && pp.p2 > 21)//A가 포함되어 있는데 hit을 한후 21이 넘으면 A값을 1로 설정
                    pp.p2 -= 10;
            result();
        }
        else if(bdoubledown != 0 && adoubledown == 0)
        {
            printf("      %10s         %14s\n", people.p2 ,people.p1);
            deal(deck,3,2);
            if((deck[8].face == 0 || deck[9].face == 0) && pp.p1 > 21)//A가 포함되어 있는데 hit을 한후 21이 넘으면 A값을 1로 설정
            {
                pp.p1 -= 10;
            }
            result();
            while(pp.p1 < 21)
            {
                printf("\n%s님 Hit OR Stand (hit : 1, stand : 0) >> ", people.p1);
                scanf("%d", &h);
                if(h == 1)
                {
                    printf("Hit!\n");
                    printf("      %10s         %14s\n", people.p2 ,people.p1);
                    deal(deck,3,2+i);
                    if((deck[8+i].face == 0 || deck[9+i].face == 0) && pp.p1 > 21)//A가 포함되어 있는데 hit을 한후 21이 넘으면 A값을 1로 설정
                            pp.p1 -= 10;
                    result();
                }
                else if(h == 0)//히트를 하지 않으면 stand로 간주
                {
                    printf("%s 님 stand!\n", people.p1);
                    printf("%s님의 총합 : %d\n", people.p1, pp.p1);
                    break;
                }
                i++;
            }
        }
        else if(bdoubledown == 0 && adoubledown != 0)
        {
            printf("      %10s         %14s\n", people.p2 ,people.p1);
            deal(deck,2,3);
            if((deck[8].face == 0 || deck[9].face == 0) && pp.p1 > 21)//A가 포함되어 있는데 hit을 한후 21이 넘으면 A값을 1로 설정
                    pp.p1 -= 10;
            result();
            int y = 0;
            while(pp.p2 < 21)
            {
                printf("\n%s님 Hit OR Stand (hit : 1, stand : 0) >> ", people.p2);
                scanf("%d", &h);
                if(h == 1)
                {
                    printf("Hit!\n");
                    printf("      %10s         %14s\n", people.p2 ,people.p1);
                    deal(deck,3+y,3);
                    if((deck[i].face == 0 || deck[1+i].face == 0) && pp.p2 > 21)//A가 포함되어 있는데 hit을 한후 21이 넘으면 A값을 1로 설정
                    {
                        pp.p2 -= 10;
                    }
                    result();
                }
                else if(h == 0)//히트를 하지 않으면 stand로 간주
                {
                    printf("%s 님 stand!\n", people.p2);
                    printf("%s님의 총합 : %d\n", people.p2, pp.p2);
                    break;
                }
                y++;
            }
        }
        else if(adoubledown == 0 && bdoubledown == 0)//더블다운이 없는 경우 정상적으로 버스트 여부를 검사한다.
        {
            int i = 0;
            while(pp.p1 < 21)//21보다 작기때문에 히트할지를 물어본다.
            {
                printf("\n%s님 Hit OR Stand (hit : 1, stand : 0) >> ", people.p1);
                scanf("%d", &h);
                if(h == 1)
                {
                    count = count + 1;//히트를 했기 때문에 카운트 증가
                    printf("Hit!\n");
                    printf("      %10s         %14s\n", people.p2 ,people.p1);
                    deal(deck,2,3+i);
                    if(((deck[8+i].face == 0 || deck[9+i].face == 0) && pp.p1 > 21) ||((deck[10+i].face == 0) && pp.p1 > 21))//A가 포함되어 있는데 hit을 한후 21이 넘으면 A값을 1로 설정
                    {
                        pp.p1 -= 10;
                    }
                    result();
                }
                else if(h == 0)//히트를 하지 않으면 stand로 간주
                {
                    printf("%s 님 stand!\n", people.p1);
                    printf("%s님의 총합 : %d\n", people.p1, pp.p1);
                    break;
                }
                i++;
            }
            i = 0;
            while(pp.p2 < 21)//위의 경우와 동일
            {
                printf("\n%s님 Hit OR Stand (hit : 1, stand : 0) >> ", people.p2);
                scanf("%d", &h);
                if(h == 1)
                {
                    printf("Hit!\n");
                    /* 첫번째 플레이어의 히트 카운터에 맞게 프린트를 한다.*/
                    if(count == 0)
                    {
                        printf("      %10s         %14s\n", people.p2 ,people.p1);
                        deal(deck,3+i,2);//히트를 안했으면 2개만 프린트
                        if(((deck[i].face == 0 || deck[1+i].face == 0 ) && pp.p2 > 21 )||((deck[i+2].face == 0) && pp.p2 > 21) )//A가 포함되어 있는데 hit을 한후 21이 넘으면 A값을 1로 설정
                        {
                            pp.p2 -= 10;
                        }
                        result();
                    }
                    else if(count == 1)
                    {
                        printf("      %10s         %14s\n", people.p2 ,people.p1);
                        deal(deck, 3+i, 3);//히트를 한 번했으면 3개 프린트
                        if(deck[2].face == 0 && pp.p2 > 21)//새로나온 A를 합했을때 21이 넘으면 A값을 1로 설정
                        {
                            pp.p2 -= 10;
                        }
                               
                        result();
                    }
                    else if(count == 2)
                    {
                        printf("      %10s         %14s\n", people.p2 ,people.p1);
                        deal(deck, 3+i, 4);//히트를 두 번했으면 4개 프린트
                        if(deck[2].face == 0 && pp.p2 > 21)//새로나온 A를 합했을때 21이 넘으면 A값을 1로 설정
                        {
                            pp.p2 -= 10;
                        }
                                
                        result();
                    }
                }
                else if(h == 0)
                {
                    printf("%s 님 stand!\n", people.p2);
                    printf("%s님의 총합 : %d\n", people.p2, pp.p2);
                    break;
                }
                i++;
            }
        }
        printf("%10s\n", "딜러의 히든카드를 공개합니다!");
        sleep(1.3);
        dealerOpendeal(deck, 2);
        sleep(1);
        printf("딜러의 총합 : %d\n", pp.dealer);
        i = 0;
        while(pp.dealer < 17)//17보다 작을경우 계속 카드를 뽑아야 한다.
        {
            
            if((bustornot(pp.p1) == 0 || bustornot(pp.p2) == 0))//둘중 하나만 버스트가 안나도 계속 진행
            {
                printf("딜러가 카드를 한장 더 뽑습니다.\n");
                sleep(1);
                dealerOpendeal(deck, 3 + i);
                printf("딜러의 총합 : %d\n", pp.dealer);
            }
            else if((bustornot(pp.p1) == 1 && bustornot(pp.p2) == 1)) //둘다 버스트가 났다면 자동으로 딜러의 승리
            {
                compare();
                printf("한번 더 하시겠습니까? (y : 1 / n : 0) >> ");
                scanf("%d", &go);
                if(go == 1)
                    continue;
                else
                    return 0;
            }
            i++;
        }
        compare();
        printf("한번 더 하시겠습니까? (y : 1 / n : 0) >> ");
        scanf("%d", &go);
        if(go == 1)
        {
            printf("\n\n");
            continue;
        }
        else
        {
            printf("\n\n");
            return 0;
        }
    }
}


/* 아래는 플레이어가 카드를 분배받는 함수*/
/* 몇장 받을지를 함수 인자로 구성해서 실행*/
void deal(card *deck, int t, int k)
{
    pp.p1 = 0;//딜 함수를 호출할때 모두 0으로 초기화
    pp.p2 = 0;
    for(int i = 0; i < 16; i++)//
    {
        printf("%3s%-10s", strface[deck[i].face], strsuit[deck[i].suit]);
        if(i < t)
        {
            if(deck[i].face == 0) //숫자가 A라면 먼저 11을 더하고 a에 1을 더해서 A가 있다는 것을 알려줌
            {
                pp.p2 += 11;
            }
            if(deck[i].face < 10 && deck[i].face > 0)
            {
                pp.p2 += deck[i].face + 1; //인덱스보다 숫자가 하나 더 크기 때문에 1을 더해줌
            }
            else if(deck[i].face >= 10) //인덱스가 10이상인것은 10, J, Q, K밖에 없고, j,q,k는 블랙잭에서 10으로 취급
            {
                pp.p2 += 10;
            }
        }
        else if(i >= 8)
        {
            if(deck[i].face == 0)
            {
                pp.p1 += 11;
            }
            if(deck[i].face < 10 && deck[i].face > 0)
            {
                pp.p1 += deck[i].face + 1;
            }
            else if(deck[i].face >= 10)
            {
                pp.p1 += 10;
            }
        }
        if(i == t-1)
        {
            i = 7;
            printf(" | "); //플레이어를 구분하기위한 구분자
        }
        if(i == k + 7)
        {
            i = 15;
            printf(" | ");
        }
    }
    printf("\n");
    checkPlayerBlackJack();
    //둘다 히트를 하지 않았을 경우에 더블 할것인지 물어본다. 히트를 했을경우 더블다운 불가능
    if(t < 3)
        checkadoubledown();
    if(k < 3)
        checkbdoubledown();
}

/* 플레이어의 블랙잭을 체크하는 함수 */
void checkPlayerBlackJack()
{
    if(pp.p2 == 21 && (deck[0].face == 0 || deck[1].face == 0))
    {
        bblackjack++;
    }
    if(pp.p1 == 21 &&  (deck[8].face == 0 || deck[9].face == 0))
    {
        bblackjack++;
    }
}
/*아래는 첫번째 플레이어 더블다운 물어보는 함수*/
void checkadoubledown()
{
    int doubledown;
    if(pp.p1 < 21)
    {
        if(adoubledown == 0)
        {
            printf("%s 님 Double 하시겠습니까? (y : 1 / n : 0) >> ", people.p1);
            scanf("%d", &doubledown);
            if(doubledown == 1)
            {
                money.p1money = money.p1money * 2;//배팅 금액을 두배로 설정하고
                adoubledown++;//더블다운 했음을 전역변수에 반환한다.
            }
        }
    }
}

/*아래는 첫번째 플레이어 더블다운 물어보는 함수*/
void checkbdoubledown()
{
    int doubledown;
    if(pp.p2 < 21)
    {
        if(bdoubledown == 0)
        {
            printf("%s 님 Double 하시겠습니까? (y : 1 / n : 0) >> ", people.p2);
            scanf("%d", &doubledown);
            if(doubledown == 1)
            {
                money.p2money = money.p2money * 2;//배팅 금액을 두배로 설정하고
                bdoubledown++;//더블다운 했음을 전역변수에 반환한다.
            }
        }
    }
}

//총합을 출력하는 함수
void result()
{
    printf("%s님의 총합 : %d\n", people.p1, pp.p1);
    printf("%s님의 총합 : %d\n", people.p2, pp.p2);
}
