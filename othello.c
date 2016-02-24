//========================ヘッダファイル========================
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
//========================大域マクロ=========================
#define SIZE 8
#define SEARCH_LEVEL 2
//========================大域定義=========================
//-- 駒型
typedef enum {WHT=-1, EMP=0, BLK=+1, OUT=+2}  Piece;

//-- 盤面型
typedef struct {
    Piece cell[SIZE][SIZE];   // 二次元配列で盤面を表す
    int heavy[SIZE][SIZE];    // 優先度
} Board;

//-- 打ち手型
typedef struct {
    int x;           // 縦
    int y;           // 横
    Piece color;     // 駒の色
} Hand;

//========================関数宣言=========================
void player(Board *brd, Piece wh, bool *pass);        // プレイヤの処理
void computerA(Board *brd, Piece wh, bool *pass);      // AIの処理
void computerB(Board *brd, Piece wh, bool *pass);      // AIの処理
void computerC(Board *brd, Piece wh, bool * pass);
int minMax(Board brd, Hand *hand, bool flag, int level);
Board brd_init(void);                       // 盤面の初期化
void brd_output(Board brd);                 // 盤面の出力
void hand_input(Hand *hand);                // 打ち手の入力
bool brd_turn(Board *brd, Hand hand);       // 盤面の更新
int brd_turn_dir(Board *brd, Hand hand, int dx, int dy);     // 指定方向への走査
bool end_check(Board brd);                  // 終了の判定
Piece cell_val(Board brd, int x, int y);    // 指定位置のマスの状態
int countStone(Board brd, Piece wh);
void winner_check(Board brd);              // 勝敗の判定
bool pass_check(Board brd, Piece wh);       // パスの判定
//========================本体処理=========================
int main(void) {
    //-- 宣言
    Board brd;          // 盤面
    bool passBLK, passWHT;

    //-- 盤面入力
    brd = brd_init();  // brdのアドレスを渡す
    brd_output(brd);  // brdのデータを渡す

    //-- ゲームループ
    while ( ! end_check(brd) ) {
        computerC(&brd,BLK,&passBLK);
        brd_output(brd);
        if ( passBLK && passWHT ) { break; }
        computerC(&brd,WHT,&passWHT);
        brd_output(brd);
        break;
        if ( passBLK && passWHT ) { break; }
    }

    //-- 勝敗判定
    winner_check(brd);

    //-- 終了
    return 0;
}
//========================プレイヤ==========================
void player(Board *brd, Piece wh, bool *pass) {
    //-- 宣言
    Hand hand;
    hand.color = wh;

    ( wh == BLK ) ? printf("黒のターン\n") : printf("白のターン\n");
    *pass = false;

    //-- パス判定
    if ( pass_check(*brd, hand.color) ) {
        printf("打てる場所がありません。パスします。\n");
        *pass = true;
        return;
    }

    while ( 1 ) {
        //-- 打ち手入力
        hand_input(&hand);
        //-- 盤面更新
        if ( brd_turn(brd, hand) ) {   // 盤面の更新と判定
            break;
        }
        printf("そこには打てません\n");
    }
    printf("%d %d\n", hand.x, hand.y);
}
//========================AIverA=========================
void computerA(Board *brd, Piece wh, bool *pass) {
    //-- 宣言
    int x, y;              // 反復変数
    int count;
    int max = 0;
    Board aibrd = *brd;
    Hand hand, aihand;
    hand.color = wh;

    ( wh == BLK ) ? printf("黒のターン\n") : printf("白のターン\n");
    *pass = false;

    //-- パス判定
    if ( pass_check(aibrd, hand.color ) ) {
        printf("打てる場所がありません。パスします。\n");
        *pass = true;
        return;
    }

    //-- 打ち手探索
    for ( x = 0; x < SIZE; x++ ) {
        for ( y = 0; y < SIZE; y++ ) {
            if ( cell_val(aibrd, x, y) != EMP ) { continue; }
            aibrd = *brd;
            hand.x = x;
            hand.y = y;
            count = 0;
            count += brd_turn_dir(&aibrd, hand, 1, 0);      // 下
            count += brd_turn_dir(&aibrd, hand, 1, 1);      // 右下
            count += brd_turn_dir(&aibrd, hand, 1, -1);     // 左下
            count += brd_turn_dir(&aibrd, hand, 0, 1);      // 右
            count += brd_turn_dir(&aibrd, hand, 0, -1);     // 左
            count += brd_turn_dir(&aibrd, hand, -1, 0);     // 上
            count += brd_turn_dir(&aibrd, hand, -1, 1);     // 右上
            count += brd_turn_dir(&aibrd, hand, -1, -1);    // 左上
            if ( max < count ) { aihand = hand; max = count; }
        }
    }

    //-- 盤面更新
    brd_turn(brd, aihand);
    printf("%d %d\n", aihand.x, aihand.y);
}
//========================AIverB==========================
void computerB(Board *brd, Piece wh, bool *pass) {
	//-- 宣言
    int x, y;              // 反復変数
    int count;
    int max = 0;
    Board aibrd = *brd;
    Hand hand, aihand;
    hand.color = wh;

    ( wh == BLK ) ? printf("黒のターン\n") : printf("白のターン\n");
    *pass = false;

    //-- パス判定
    if ( pass_check(aibrd, hand.color ) ) {
        printf("打てる場所がありません。パスします。\n");
        *pass = true;
        return;
    }

    //-- 打ち手探索
    for ( x = 0; x < SIZE; x++ ) {
        for ( y = 0; y < SIZE; y++ ) {
            if ( cell_val(aibrd, x, y) != EMP ) { continue; }
            aibrd = *brd;
            hand.x = x;
            hand.y = y;
            count = 0;
            count += brd_turn_dir(&aibrd, hand, 1, 0);      // 下
            count += brd_turn_dir(&aibrd, hand, 1, 1);      // 右下
            count += brd_turn_dir(&aibrd, hand, 1, -1);     // 左下
            count += brd_turn_dir(&aibrd, hand, 0, 1);      // 右
            count += brd_turn_dir(&aibrd, hand, 0, -1);     // 左
            count += brd_turn_dir(&aibrd, hand, -1, 0);     // 上
            count += brd_turn_dir(&aibrd, hand, -1, 1);     // 右上
            count += brd_turn_dir(&aibrd, hand, -1, -1);    // 左上
            count *= brd->heavy[x][y];
            if ( max < count ) { aihand = hand; max = count; }
        }
    }

    //-- 盤面更新
    brd_turn(brd, aihand);
    printf("%d %d\n", aihand.x, aihand.y);
}
//========================AIverC==========================
void computerC(Board *brd, Piece wh, bool *pass) {
    bool flag = true;
    Hand aihand;

    ( wh == BLK ) ? printf("黒のターン\n") : printf("白のターン\n");
    *pass = false;

    //-- パス判定
    if ( pass_check(*brd, wh) ) {
        printf("打てる場所がありません。パスします。\n");
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

    //-- 末端判定
    if ( level == 0 ) {
        return ( flag ) ? countStone(brd, wh) : countStone(brd, -wh);
    }
    //-- パス判定
    if ( pass_check(aibrd, hand->color ) ) {
        return ( flag ) ? countStone(brd, wh) : countStone(brd, -wh);
    }

    if ( flag ) {
        //-- 自分の手番なら最小にセット
        value = INT_MIN;
        printf("PLATER %d\n", value);
    } else {
        //-- 相手の手番なら最大にセット
        value = INT_MAX;
        printf("ENEMY %d\n", value);
    }

    for ( x = 0; x < SIZE; x++ ) {
        for ( y = 0; y < SIZE; y++ ) {
            //-- 試しに打つ
            aibrd = brd;
            aihand.x = x;
            aihand.y = y;
            if ( brd_turn(&aibrd, aihand) ) { continue; }
            printf("hoge\n" );
            brd_output(aibrd);
            //-- 再帰で相手の手を評価
            if ( flag ) { next = false; } else { next = true; }
            if ( next ) { printf("AI\n"); } else { printf("PLAYER\n"); }
            aihand.color = -wh;
            childValue = minMax(aibrd, &aihand, next, level-1);
            printf("%d\n", childValue);
            //-- 子ノードとの評価値を比較する
            if ( flag ) {
                //-- AIの手番なら子ノードの中で最大の評価値を選ぶ
                if ( childValue > value ) {
                    value = childValue;
                    bestX = x;
                    bestY = y;
                }
            } else {
                //-- プレイヤの手番なら子ノードの中で最小の評価値を選ぶ
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
        //-- ルートノードなら最大評価値を持つ場所を返す
        return bestX + bestY * SIZE;
    } else {
        //-- 子ノードならノードの評価値を返す
        return value;
    }
}
//========================盤面入力=========================
Board brd_init(void) {
    //-- 宣言
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

//========================盤面出力=========================
void brd_output(Board brd) {
    //-- 宣言
    int x, y;    // 反復変数

    //-- 出力処理
    printf("  ");
    for ( y = 0; y < SIZE; y++ ) { printf("Y%d",y);}
    for ( x = 0; x < SIZE; x++) {
        printf("\nX");
        printf("%d",x);
        for ( y = 0; y < SIZE; y++ ) {
            switch ( brd.cell[x][y] ) {
                case WHT: printf("○");   break;
                case EMP: printf("・");   break;
                case BLK: printf("●");   break;
                default : printf("？");
            }
        }
    }
    printf("\n\n");
}

//========================打手入力=========================
void hand_input(Hand *hand) {
    //-- 宣言
    int x, y;

    //--入力処理
    while ( 1 ) {
        printf("X > ");
        scanf("%d", &x);
        if ( x >= 0 && x < SIZE ) { break; }    // 正しい入力なら反復を脱出
        printf("不正な入力です。  再入力してください。\n");
    }

    while ( 1 ) {
        printf("Y > ");
        scanf("%d", &y);
        if ( y >= 0 && y < SIZE ) { break; }    // 正しい入力なら反復を脱出
        printf("不正な入力です。  再入力してください。\n");
    }

    //-- 格納
    hand->x = x;
    hand->y = y;
}
//========================盤面更新=========================
bool brd_turn(Board *brd, Hand hand) {
    //-- 宣言
    int count = 0;    // ひっくり返した駒の数

    //-- 打つ位置がEMPでないなら失敗
    if ( cell_val(*brd, hand.x, hand.y) != EMP ) { return false; }

    //-- 打つ位置から上下左右斜め８方向への走査
    count += brd_turn_dir(brd, hand, 1, 0);      // 下
    count += brd_turn_dir(brd, hand, 1, 1);      // 右下
    count += brd_turn_dir(brd, hand, 1, -1);     // 左下
    count += brd_turn_dir(brd, hand, 0, 1);      // 右
    count += brd_turn_dir(brd, hand, 0, -1);     // 左
    count += brd_turn_dir(brd, hand, -1, 0);     // 上
    count += brd_turn_dir(brd, hand, -1, 1);     // 右上
    count += brd_turn_dir(brd, hand, -1, -1);    // 左上

    //-- 駒をひっくり返せなければ失敗
    if ( count == 0 ) { return false; }
    //printf("%d %d\n", hand.x, hand.y);

    //-- 返却
    return true;
}
//=====================指定方向への盤面走査=====================
int brd_turn_dir(Board *brd, Hand hand, int dx, int dy) {
    //-- 宣言
    int tx = hand.x;          // 現在位置
    int ty = hand.y;          // 現在位置
    Piece wh = hand.color;    // 自分の駒
    int len = 0;              // 相手の駒の連長

    //-- はさんでいるか判定
    while ( 1 ) {
        //- 現在位置を指定方向に更新
        tx += dx;
        ty += dy;
        //- 現在位置が相手の駒なら連長を増分
        if ( cell_val(*brd, tx, ty) == -wh ) { len++; }
        //- 連長が正で自分の駒なら打ち切り
        else if ( len > 0 && cell_val(*brd, tx, ty) == wh ) { break; }
        //- どちらでもない(盤外か空マス)なら0を返す
        else { return 0; }
    }

    //-- 駒をひっくり返す
    while ( 1 ) {
        //- 現在位置から指定方向の逆へ更新
        tx -= dx;
        ty -= dy;
        //- 駒が相手の駒でないなら打ち切り
        if ( cell_val(*brd, tx, ty) != -wh ) { break; }
        //- 自分の駒に更新
        brd->cell[tx][ty] = wh;
    }

    //-- 打つ位置に自分の駒を置く
    brd->cell[hand.x][hand.y] = wh;
    //-- 返却
    return len;
}
//=====================指定位置の駒の状態======================
Piece cell_val(Board brd, int x, int y) {
    //-- 盤外ならOUTを返却
    if ( x < 0 || x >= SIZE ) { return OUT; }
    if ( y < 0 || y >= SIZE ) { return OUT; }

    //-- 駒の状態を返却
    return brd.cell[x][y];
}
//========================勝敗判定=========================
void winner_check(Board brd) {
    //-- 宣言
    int black, white;  // 駒の数

    //-- カウント
    black = countStone(brd, BLK);
    white = countStone(brd, WHT);

    //-- 判定
    printf("黒 : 白\n");
    printf("%2d : %2d\n", black, white);
    if ( black > white ) { printf("黒の勝ち\n"); }
    else if ( black == white ) { printf("引き分け\n"); }
    else { printf("白の勝ち\n"); }
}
//========================石カウント=========================
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
//========================パス判定=========================
bool pass_check(Board brd, Piece wh) {
    int x, y;    // 反復変数
    Hand tmp;
    tmp.color = wh;

    //-- おける場所があるか走査
    for ( x = 0; x < SIZE; x++ ) {
        tmp.x = x;
        for ( y = 0; y < SIZE; y++ ) {
            tmp.y = y;
            if ( brd_turn(&brd, tmp) ) { return false; }
        }
    }

    //-- 返却
    return true;

}
//========================終了判定=========================
bool end_check(Board brd) {
    int x, y;
    for ( x = 0; x < SIZE; x++ ) {
        for ( y = 0; y < SIZE; y++ ) {
            if ( brd.cell[x][y] == EMP ) {   // brd.cell[x][y]がEMPか調べる
                return false;                // EMPならfalseを返す
            }
        }
    }
    return true;    // EMPがなければ終了
}
