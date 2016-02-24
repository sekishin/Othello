//========================�w�b�_�t�@�C��========================
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
//========================���}�N��=========================
#define SIZE 8
#define SEARCH_LEVEL 2
//========================����`=========================
//-- ��^
typedef enum {WHT=-1, EMP=0, BLK=+1, OUT=+2}  Piece;

//-- �Ֆʌ^
typedef struct {
    Piece cell[SIZE][SIZE];   // �񎟌��z��ŔՖʂ�\��
    int heavy[SIZE][SIZE];    // �D��x
} Board;

//-- �ł���^
typedef struct {
    int x;           // �c
    int y;           // ��
    Piece color;     // ��̐F
} Hand;

//========================�֐��錾=========================
void player(Board *brd, Piece wh, bool *pass);        // �v���C���̏���
void computerA(Board *brd, Piece wh, bool *pass);      // AI�̏���
void computerB(Board *brd, Piece wh, bool *pass);      // AI�̏���
void computerC(Board *brd, Piece wh, bool * pass);
int minMax(Board brd, Hand *hand, bool flag, int level);
Board brd_init(void);                       // �Ֆʂ̏�����
void brd_output(Board brd);                 // �Ֆʂ̏o��
void hand_input(Hand *hand);                // �ł���̓���
bool brd_turn(Board *brd, Hand hand);       // �Ֆʂ̍X�V
int brd_turn_dir(Board *brd, Hand hand, int dx, int dy);     // �w������ւ̑���
bool end_check(Board brd);                  // �I���̔���
Piece cell_val(Board brd, int x, int y);    // �w��ʒu�̃}�X�̏��
int countStone(Board brd, Piece wh);
void winner_check(Board brd);              // ���s�̔���
bool pass_check(Board brd, Piece wh);       // �p�X�̔���
//========================�{�̏���=========================
int main(void) {
    //-- �錾
    Board brd;          // �Ֆ�
    bool passBLK, passWHT;

    //-- �Ֆʓ���
    brd = brd_init();  // brd�̃A�h���X��n��
    brd_output(brd);  // brd�̃f�[�^��n��

    //-- �Q�[�����[�v
    while ( ! end_check(brd) ) {
        computerC(&brd,BLK,&passBLK);
        brd_output(brd);
        if ( passBLK && passWHT ) { break; }
        computerC(&brd,WHT,&passWHT);
        brd_output(brd);
        break;
        if ( passBLK && passWHT ) { break; }
    }

    //-- ���s����
    winner_check(brd);

    //-- �I��
    return 0;
}
//========================�v���C��==========================
void player(Board *brd, Piece wh, bool *pass) {
    //-- �錾
    Hand hand;
    hand.color = wh;

    ( wh == BLK ) ? printf("���̃^�[��\n") : printf("���̃^�[��\n");
    *pass = false;

    //-- �p�X����
    if ( pass_check(*brd, hand.color) ) {
        printf("�łĂ�ꏊ������܂���B�p�X���܂��B\n");
        *pass = true;
        return;
    }

    while ( 1 ) {
        //-- �ł������
        hand_input(&hand);
        //-- �ՖʍX�V
        if ( brd_turn(brd, hand) ) {   // �Ֆʂ̍X�V�Ɣ���
            break;
        }
        printf("�����ɂ͑łĂ܂���\n");
    }
    printf("%d %d\n", hand.x, hand.y);
}
//========================AIverA=========================
void computerA(Board *brd, Piece wh, bool *pass) {
    //-- �錾
    int x, y;              // �����ϐ�
    int count;
    int max = 0;
    Board aibrd = *brd;
    Hand hand, aihand;
    hand.color = wh;

    ( wh == BLK ) ? printf("���̃^�[��\n") : printf("���̃^�[��\n");
    *pass = false;

    //-- �p�X����
    if ( pass_check(aibrd, hand.color ) ) {
        printf("�łĂ�ꏊ������܂���B�p�X���܂��B\n");
        *pass = true;
        return;
    }

    //-- �ł���T��
    for ( x = 0; x < SIZE; x++ ) {
        for ( y = 0; y < SIZE; y++ ) {
            if ( cell_val(aibrd, x, y) != EMP ) { continue; }
            aibrd = *brd;
            hand.x = x;
            hand.y = y;
            count = 0;
            count += brd_turn_dir(&aibrd, hand, 1, 0);      // ��
            count += brd_turn_dir(&aibrd, hand, 1, 1);      // �E��
            count += brd_turn_dir(&aibrd, hand, 1, -1);     // ����
            count += brd_turn_dir(&aibrd, hand, 0, 1);      // �E
            count += brd_turn_dir(&aibrd, hand, 0, -1);     // ��
            count += brd_turn_dir(&aibrd, hand, -1, 0);     // ��
            count += brd_turn_dir(&aibrd, hand, -1, 1);     // �E��
            count += brd_turn_dir(&aibrd, hand, -1, -1);    // ����
            if ( max < count ) { aihand = hand; max = count; }
        }
    }

    //-- �ՖʍX�V
    brd_turn(brd, aihand);
    printf("%d %d\n", aihand.x, aihand.y);
}
//========================AIverB==========================
void computerB(Board *brd, Piece wh, bool *pass) {
	//-- �錾
    int x, y;              // �����ϐ�
    int count;
    int max = 0;
    Board aibrd = *brd;
    Hand hand, aihand;
    hand.color = wh;

    ( wh == BLK ) ? printf("���̃^�[��\n") : printf("���̃^�[��\n");
    *pass = false;

    //-- �p�X����
    if ( pass_check(aibrd, hand.color ) ) {
        printf("�łĂ�ꏊ������܂���B�p�X���܂��B\n");
        *pass = true;
        return;
    }

    //-- �ł���T��
    for ( x = 0; x < SIZE; x++ ) {
        for ( y = 0; y < SIZE; y++ ) {
            if ( cell_val(aibrd, x, y) != EMP ) { continue; }
            aibrd = *brd;
            hand.x = x;
            hand.y = y;
            count = 0;
            count += brd_turn_dir(&aibrd, hand, 1, 0);      // ��
            count += brd_turn_dir(&aibrd, hand, 1, 1);      // �E��
            count += brd_turn_dir(&aibrd, hand, 1, -1);     // ����
            count += brd_turn_dir(&aibrd, hand, 0, 1);      // �E
            count += brd_turn_dir(&aibrd, hand, 0, -1);     // ��
            count += brd_turn_dir(&aibrd, hand, -1, 0);     // ��
            count += brd_turn_dir(&aibrd, hand, -1, 1);     // �E��
            count += brd_turn_dir(&aibrd, hand, -1, -1);    // ����
            count *= brd->heavy[x][y];
            if ( max < count ) { aihand = hand; max = count; }
        }
    }

    //-- �ՖʍX�V
    brd_turn(brd, aihand);
    printf("%d %d\n", aihand.x, aihand.y);
}
//========================AIverC==========================
void computerC(Board *brd, Piece wh, bool *pass) {
    bool flag = true;
    Hand aihand;

    ( wh == BLK ) ? printf("���̃^�[��\n") : printf("���̃^�[��\n");
    *pass = false;

    //-- �p�X����
    if ( pass_check(*brd, wh) ) {
        printf("�łĂ�ꏊ������܂���B�p�X���܂��B\n");
        *pass = true;
        return;
    }

    aihand.color = wh;
    minMax(*brd, &aihand, flag, SEARCH_LEVEL);
    aihand.color = wh;
    //printf("%d %d\n", aihand.x, aihand.y);
    brd_turn(brd, aihand);
}

int minMax(Board brd, Hand *hand, bool flag, int level) {
    int bestX = 0;
    int bestY = 0;
    int value, childValue;
    int x, y, count;
    bool next;
    Board aibrd = brd;
    Hand aihand;
    Piece wh = hand->color;

    //-- ���[����
    if ( level == 0 ) {
        return ( flag ) ? countStone(brd, wh) : countStone(brd, -wh);
    }
    //-- �p�X����
    if ( pass_check(aibrd, hand->color ) ) {
        return ( flag ) ? countStone(brd, wh) : countStone(brd, -wh);
    }

    if ( flag ) {
        //-- �����̎�ԂȂ�ŏ��ɃZ�b�g
        value = INT_MIN;
        printf("PLATER %d\n", value);
    } else {
        //-- ����̎�ԂȂ�ő�ɃZ�b�g
        value = INT_MAX;
        printf("ENEMY %d\n", value);
    }

    for ( x = 0; x < SIZE; x++ ) {
        for ( y = 0; y < SIZE; y++ ) {
            //-- �����ɑł�
            aibrd = brd;
            aihand.x = x;
            aihand.y = y;
            if ( brd_turn(&aibrd, aihand) ) { continue; }
            printf("hoge\n" );
            brd_output(aibrd);
            //-- �ċA�ő���̎��]��
            if ( flag ) { next = false; } else { next = true; }
            if ( next ) { printf("AI\n"); } else { printf("PLAYER\n"); }
            aihand.color = -wh;
            childValue = minMax(aibrd, &aihand, next, level-1);
            printf("%d\n", childValue);
            //-- �q�m�[�h�Ƃ̕]���l���r����
            if ( flag ) {
                //-- AI�̎�ԂȂ�q�m�[�h�̒��ōő�̕]���l��I��
                if ( childValue > value ) {
                    value = childValue;
                    bestX = x;
                    bestY = y;
                }
            } else {
                //-- �v���C���̎�ԂȂ�q�m�[�h�̒��ōŏ��̕]���l��I��
                if ( childValue < value ) {
                    value = childValue;
                    bestX = x;
                    bestY = y;
                }
            }

        }
    }
    hand->x = bestX;
    hand->y = bestY;
    //printf("%d %d\n", bestX, bestY);
    if ( level = SEARCH_LEVEL ) {
        //-- ���[�g�m�[�h�Ȃ�ő�]���l�����ꏊ��Ԃ�
        return bestX + bestY * SIZE;
    } else {
        //-- �q�m�[�h�Ȃ�m�[�h�̕]���l��Ԃ�
        return value;
    }
}
//========================�Ֆʓ���=========================
Board brd_init(void) {
    //-- �錾
    Board tmp = {
        EMP, EMP, EMP, EMP, EMP, EMP, EMP, EMP,
        EMP, EMP, EMP, EMP, EMP, EMP, EMP, EMP,
        EMP, EMP, EMP, EMP, EMP, EMP, EMP, EMP,
        EMP, EMP, EMP, WHT, BLK, EMP, EMP, EMP,
        EMP, EMP, EMP, BLK, WHT, EMP, EMP, EMP,
        EMP, EMP, EMP, EMP, EMP, EMP, EMP, EMP,
        EMP, EMP, EMP, EMP, EMP, EMP, EMP, EMP,
        EMP, EMP, EMP, EMP, EMP, EMP, EMP, EMP,
        10,  1,   7,   7,   7,   7,   1,   10,
        1,   1,   3,   3,   3,   3,   1,   1,
        7,   3,   5,   5,   5,   5,   3,   7,
        7,   3,   5,   5,   5,   5,   3,   7,
        7,   3,   5,   5,   5,   5,   3,   7,
        7,   3,   5,   5,   5,   5,   3,   7,
        1,   1,   3,   3,   3,   3,   1,   1,
        10,  1,   7,   7,   7,   7,   1,   10,
    };

    return tmp;
}

//========================�Ֆʏo��=========================
void brd_output(Board brd) {
    //-- �錾
    int x, y;    // �����ϐ�

    //-- �o�͏���
    printf("  ");
    for ( y = 0; y < SIZE; y++ ) { printf("Y%d",y);}
    for ( x = 0; x < SIZE; x++) {
        printf("\nX");
        printf("%d",x);
        for ( y = 0; y < SIZE; y++ ) {
            switch ( brd.cell[x][y] ) {
                case WHT: printf("��");   break;
                case EMP: printf("�E");   break;
                case BLK: printf("��");   break;
                default : printf("�H");
            }
        }
    }
    printf("\n\n");
}

//========================�Ŏ����=========================
void hand_input(Hand *hand) {
    //-- �錾
    int x, y;

    //--���͏���
    while ( 1 ) {
        printf("X > ");
        scanf("%d", &x);
        if ( x >= 0 && x < SIZE ) { break; }    // ���������͂Ȃ甽����E�o
        printf("�s���ȓ��͂ł��B  �ē��͂��Ă��������B\n");
    }

    while ( 1 ) {
        printf("Y > ");
        scanf("%d", &y);
        if ( y >= 0 && y < SIZE ) { break; }    // ���������͂Ȃ甽����E�o
        printf("�s���ȓ��͂ł��B  �ē��͂��Ă��������B\n");
    }

    //-- �i�[
    hand->x = x;
    hand->y = y;
}
//========================�ՖʍX�V=========================
bool brd_turn(Board *brd, Hand hand) {
    //-- �錾
    int count = 0;    // �Ђ�����Ԃ�����̐�

    //-- �łʒu��EMP�łȂ��Ȃ玸�s
    if ( cell_val(*brd, hand.x, hand.y) != EMP ) { return false; }

    //-- �łʒu����㉺���E�΂߂W�����ւ̑���
    count += brd_turn_dir(brd, hand, 1, 0);      // ��
    count += brd_turn_dir(brd, hand, 1, 1);      // �E��
    count += brd_turn_dir(brd, hand, 1, -1);     // ����
    count += brd_turn_dir(brd, hand, 0, 1);      // �E
    count += brd_turn_dir(brd, hand, 0, -1);     // ��
    count += brd_turn_dir(brd, hand, -1, 0);     // ��
    count += brd_turn_dir(brd, hand, -1, 1);     // �E��
    count += brd_turn_dir(brd, hand, -1, -1);    // ����

    //-- ����Ђ�����Ԃ��Ȃ���Ύ��s
    if ( count == 0 ) { return false; }
    //printf("%d %d\n", hand.x, hand.y);

    //-- �ԋp
    return true;
}
//=====================�w������ւ̔Ֆʑ���=====================
int brd_turn_dir(Board *brd, Hand hand, int dx, int dy) {
    //-- �錾
    int tx = hand.x;          // ���݈ʒu
    int ty = hand.y;          // ���݈ʒu
    Piece wh = hand.color;    // �����̋�
    int len = 0;              // ����̋�̘A��

    //-- �͂���ł��邩����
    while ( 1 ) {
        //- ���݈ʒu���w������ɍX�V
        tx += dx;
        ty += dy;
        //- ���݈ʒu������̋�Ȃ�A���𑝕�
        if ( cell_val(*brd, tx, ty) == -wh ) { len++; }
        //- �A�������Ŏ����̋�Ȃ�ł��؂�
        else if ( len > 0 && cell_val(*brd, tx, ty) == wh ) { break; }
        //- �ǂ���ł��Ȃ�(�ՊO����}�X)�Ȃ�0��Ԃ�
        else { return 0; }
    }

    //-- ����Ђ�����Ԃ�
    while ( 1 ) {
        //- ���݈ʒu����w������̋t�֍X�V
        tx -= dx;
        ty -= dy;
        //- �����̋�łȂ��Ȃ�ł��؂�
        if ( cell_val(*brd, tx, ty) != -wh ) { break; }
        //- �����̋�ɍX�V
        brd->cell[tx][ty] = wh;
    }

    //-- �łʒu�Ɏ����̋��u��
    brd->cell[hand.x][hand.y] = wh;
    //-- �ԋp
    return len;
}
//=====================�w��ʒu�̋�̏��======================
Piece cell_val(Board brd, int x, int y) {
    //-- �ՊO�Ȃ�OUT��ԋp
    if ( x < 0 || x >= SIZE ) { return OUT; }
    if ( y < 0 || y >= SIZE ) { return OUT; }

    //-- ��̏�Ԃ�ԋp
    return brd.cell[x][y];
}
//========================���s����=========================
void winner_check(Board brd) {
    //-- �錾
    int black, white;  // ��̐�

    //-- �J�E���g
    black = countStone(brd, BLK);
    white = countStone(brd, WHT);

    //-- ����
    printf("�� : ��\n");
    printf("%2d : %2d\n", black, white);
    if ( black > white ) { printf("���̏���\n"); }
    else if ( black == white ) { printf("��������\n"); }
    else { printf("���̏���\n"); }
}
//========================�΃J�E���g=========================
int countStone(Board brd, Piece wh) {
    int x, y;
    int count = 0;

    for ( x = 0; x < SIZE; x++ ) {
        for ( y = 0; y < SIZE; y++ ) {
            if ( brd.cell[x][y] == wh ) { count++; }
        }
    }

    return count;
}
//========================�p�X����=========================
bool pass_check(Board brd, Piece wh) {
    int x, y;    // �����ϐ�
    Hand tmp;
    tmp.color = wh;

    //-- ������ꏊ�����邩����
    for ( x = 0; x < SIZE; x++ ) {
        tmp.x = x;
        for ( y = 0; y < SIZE; y++ ) {
            tmp.y = y;
            if ( brd_turn(&brd, tmp) ) { return false; }
        }
    }

    //-- �ԋp
    return true;

}
//========================�I������=========================
bool end_check(Board brd) {
    int x, y;
    for ( x = 0; x < SIZE; x++ ) {
        for ( y = 0; y < SIZE; y++ ) {
            if ( brd.cell[x][y] == EMP ) {   // brd.cell[x][y]��EMP�����ׂ�
                return false;                // EMP�Ȃ�false��Ԃ�
            }
        }
    }
    return true;    // EMP���Ȃ���ΏI��
}
