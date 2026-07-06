/* ============================================================
   TEBAK KATA - Robotika Edition  (VERSI FINAL)
   Proyek Akhir Praktikum Dasar Pemrograman
   ------------------------------------------------------------
   Kompilasi:  gcc -Wall -o tebak_kata tebak_kata.c
   Menjalankan: ./tebak_kata        (Linux/Mac)
                tebak_kata.exe       (Windows)
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MAX_WRONG   6      /* kepala, badan, 2 tangan, 2 kaki */
#define MAX_WORDS   50
#define HOF_SIZE    10
#define NAME_LEN    20
#define WORD_LEN    30

/* ---------- STRUCT ---------- */
struct Date {                  /* struct bersarang */
    int day, month, year;
};

struct ScoreEntry {
    char name[NAME_LEN];
    int  points;
    struct Date achieved;      /* Date bersarang di dalam ScoreEntry */
};

struct Game {
    char secret[WORD_LEN];     /* kata rahasia            */
    char display[WORD_LEN];    /* topeng tampilan: _ _ _  */
    char guessed[WORD_LEN];    /* huruf yang sudah ditebak*/
    int  guessed_count;
    int  wrong;                /* jumlah tebakan salah    */
};

/* ---------- VARIABEL GLOBAL ---------- */
const char *word_bank[MAX_WORDS] = {
    "ALGORITMA", "MOTOR", "NEURON", "ROBOTIKA", "SENSOR"
};
int word_count = 5;

struct ScoreEntry hall_of_fame[HOF_SIZE];
int hof_count = 0;

/* ---------- PROTOTIPE FUNGSI ---------- */
void print_banner(void);
int  show_menu(void);
void play_game(void);
void draw_hangman(int wrong);
int  process_guess(struct Game *g, char letter);
int  linear_search_char(const char *arr, int n, char target);
int  is_won(const struct Game *g);
int  binary_search_word(const char *bank[], int n, const char *target);
void insert_word_sorted(const char *bank[], int *n, const char *new_word);
void bubble_sort_hof(struct ScoreEntry hof[], int n);
void show_hall_of_fame(void);
void add_word(void);
void save_score(const char *name, int points);
void to_upper_str(char *s);

/* ============================================================
   MAIN - menu menggunakan do-while
   ============================================================ */
int main(void) {
    int choice;
    srand((unsigned) time(NULL));

    do {
        choice = show_menu();
        switch (choice) {
            case 1: play_game();         break;
            case 2: show_hall_of_fame(); break;
            case 3: add_word();          break;
            case 0: printf("\nTerima kasih telah bermain!\n"); break;
            default: printf("\nPilihan tidak valid. Coba lagi.\n");
        }
    } while (choice != 0);

    return 0;
}

/* ---------- FUNGSI UTILITAS UI ---------- */
void print_banner(void) {
    printf("\n========================================\n");
    printf("   TEBAK KATA - Robotika Edition\n");
    printf("========================================\n");
}

int show_menu(void) {
    int choice;
    print_banner();
    printf("  [1] Main game baru\n");
    printf("  [2] Lihat Hall of Fame\n");
    printf("  [3] Tambah kata ke bank\n");
    printf("  [0] Keluar\n");
    printf("Pilih: ");
    
    // Penanganan input menu agar tidak looping jika input bukan angka
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); // Bersihkan buffer
        return -1;
    }
    return choice;
}

void draw_hangman(int wrong) {
    printf("\n   +---+\n");
    printf("   |   |\n");
    printf("   %c   |\n", (wrong >= 1) ? 'O' : ' ');
    printf("  %c%c%c  |\n",
           (wrong >= 3) ? '/' : ' ',
           (wrong >= 2) ? '|' : ' ',
           (wrong >= 4) ? '\\' : ' ');
    printf("  %c %c  |\n",
           (wrong >= 5) ? '/' : ' ',
           (wrong >= 6) ? '\\' : ' ');
    printf("  =========\n");
}

/* ============================================================
   LOGIKA INTI PERMAINAN
   ============================================================ */
void play_game(void) {
    struct Game g;
    char name[NAME_LEN];
    int idx, len, i;
    char letter;

    idx = rand() % word_count;
    strcpy(g.secret, word_bank[idx]);
    len = strlen(g.secret);

    g.wrong = 0;
    g.guessed_count = 0;

    for (i = 0; i < len; i++) {
        g.display[i] = '_';
    }
    g.display[len] = '\0';

    printf("\nMasukkan nama pemain: ");
    if (scanf(" %19[^\n]", name) != 1) {
        strcpy(name, "Anonim"); 
    }
    printf("Kata dipilih! Panjang: %d huruf.\n", len);

    while (g.wrong < MAX_WRONG && !is_won(&g)) {
        draw_hangman(g.wrong);
        printf("\nKata  : ");
        for (i = 0; g.display[i] != '\0'; i++) {
            printf("%c ", g.display[i]);
        }
        printf("\nNyawa : %d   Salah ditebak: ", MAX_WRONG - g.wrong);
        if (g.guessed_count == 0) {
            printf("(belum ada)");
        } else {
            for (i = 0; i < g.guessed_count; i++) {
                printf("%c ", g.guessed[i]);
            }
        }

        printf("\nTebak 1 huruf: ");
        if (scanf(" %c", &letter) != 1) {
            continue;
        }
        letter = toupper((unsigned char) letter);

        if (!isalpha((unsigned char) letter)) {
            printf("--> Masukan tidak valid, harap masukkan sebuah huruf!\n");
            continue;
        }

        if (linear_search_char(g.guessed, g.guessed_count, letter) != -1) {
            printf("--> Huruf '%c' sudah pernah ditebak! Coba huruf lain.\n", letter);
            continue;
        }

        g.guessed[g.guessed_count] = letter;
        g.guessed_count++;

        if (process_guess(&g, letter)) {
            printf("--> Benar! Huruf '%c' ada di kata.\n", letter);
        } else {
            printf("--> Salah! '%c' tidak ada. (nyawa berkurang)\n", letter);
        }
    }

    if (is_won(&g)) {
        draw_hangman(g.wrong);
        printf("\n*** SELAMAT %s! Kamu menebak kata: %s ***\n", name, g.secret);
        int sisa_nyawa = MAX_WRONG - g.wrong;
        int skor = sisa_nyawa * 100 + len * 20;
        printf("Nyawa tersisa: %d\n", sisa_nyawa);
        printf("Skor = (%d x 100) + (%d x 20) = %d\n", sisa_nyawa, len, skor);
        save_score(name, skor);
    } else {
        draw_hangman(g.wrong);
        printf("\n=== GAME OVER ===\n");
        printf("Maaf %s, Anda kalah. Kata yang benar adalah: %s\n", name, g.secret);
    }
}

int process_guess(struct Game *g, char letter) {
    int found = 0;
    char *p = g->secret;
    int idx = 0;

    while (*p != '\0') {
        if (*p == letter) {
            g->display[idx] = letter;
            found = 1;
        }
        p++;
        idx++;
    }

    if (!found) {
        g->wrong++;
    }
    return found;
}

int linear_search_char(const char *arr, int n, char target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int is_won(const struct Game *g) {
    int len = strlen(g->display);
    for (int i = 0; i < len; i++) {
        if (g->display[i] == '_') {
            return 0; 
        }
    }
    return 1;
}

/* ============================================================
   MANAJEMEN BANK KATA (SEARCHING & SORTING)
   ============================================================ */
int binary_search_word(const char *bank[], int n, const char *target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(bank[mid], target);

        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

void insert_word_sorted(const char *bank[], int *n, const char *new_word) {
    if (*n >= MAX_WORDS) {
        printf("--> Gagal: Bank kata sudah penuh!\n");
        return;
    }

    char *copy = malloc(strlen(new_word) + 1);
    if (copy == NULL) {
        printf("--> Gagal: alokasi memori tidak berhasil.\n");
        return;
    }
    strcpy(copy, new_word);

    int i = *n - 1;
    while (i >= 0 && strcmp(bank[i], copy) > 0) {
        bank[i + 1] = bank[i];
        i--;
    }

    bank[i + 1] = copy;
    (*n)++;
}

void add_word(void) {
    char buf[WORD_LEN];

    printf("\nMasukkan kata baru: ");
    if (scanf(" %29s", buf) != 1) {
        printf("--> Gagal membaca masukan.\n");
        return;
    }

    for (int i = 0; buf[i] != '\0'; i++) {
        if (!isalpha((unsigned char) buf[i])) {
            printf("--> Gagal: kata hanya boleh berisi huruf!\n");
            return;
        }
    }

    to_upper_str(buf);

    printf("  Mengecek bank kata (binary search)...\n");
    if (binary_search_word(word_bank, word_count, buf) != -1) {
        printf("  '%s' sudah ada di bank kata.\n", buf);
    } else {
        printf("  '%s' belum ada. Menyisipkan pada posisi terurut...\n", buf);
        insert_word_sorted(word_bank, &word_count, buf);

        printf("  Bank kata sekarang:");
        for (int i = 0; i < word_count; i++) {
            printf(" %s", word_bank[i]);
        }
        printf("\n  Kata berhasil ditambahkan.\n");
    }
}

/* ============================================================
   MANAJEMEN PAPAN PERINGKAT
   ============================================================ */
void bubble_sort_hof(struct ScoreEntry hof[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (hof[j].points < hof[j + 1].points) {
                struct ScoreEntry temp = hof[j];
                hof[j] = hof[j + 1];
                hof[j + 1] = temp;
            }
        }
    }
}

void show_hall_of_fame(void) {
    if (hof_count == 0) {
        printf("\nBelum ada rekor yang tercatat di Hall of Fame.\n");
        return;
    }

    printf("\n========== HALL OF FAME ==========\n");
    printf("%-5s%-15s%-8s%s\n", "Rank", "Nama", "Skor", "Tanggal");
    printf("----  --------        ------  ----------\n");

    for (int i = 0; i < hof_count; i++) {
        printf("%-5d %-15s %-6d %02d/%02d/%d\n",
               i + 1,
               hall_of_fame[i].name,
               hall_of_fame[i].points,
               hall_of_fame[i].achieved.day,
               hall_of_fame[i].achieved.month,
               hall_of_fame[i].achieved.year);
    }
    printf("===================================\n");
}

void save_score(const char *name, int points) {
    char ans;

    printf("\nApakah skor ini layak masuk Hall of Fame? (Y/T): ");
    if (scanf(" %c", &ans) != 1) {
        return; 
    }
    ans = toupper((unsigned char) ans);

    if (ans != 'Y') {
        return;
    }

    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    struct Date today;
    today.day   = lt->tm_mday;
    today.month = lt->tm_mon + 1;
    today.year  = lt->tm_year + 1900;

    if (hof_count < HOF_SIZE) {
        strcpy(hall_of_fame[hof_count].name, name);
        hall_of_fame[hof_count].points = points;
        hall_of_fame[hof_count].achieved = today;
        hof_count++;

        bubble_sort_hof(hall_of_fame, hof_count);
        printf("--> Skor %s (%d) berhasil disimpan, tanggal %02d/%02d/%d.\n",
               name, points, today.day, today.month, today.year);
    } else if (points > hall_of_fame[HOF_SIZE - 1].points) {
        strcpy(hall_of_fame[HOF_SIZE - 1].name, name);
        hall_of_fame[HOF_SIZE - 1].points = points;
        hall_of_fame[HOF_SIZE - 1].achieved = today;

        bubble_sort_hof(hall_of_fame, HOF_SIZE);
        printf("--> Luar biasa! Skor Anda menggeser peringkat terbawah Hall of Fame!\n");
    } else {
        printf("--> Skor Anda belum cukup tinggi untuk masuk ke Hall of Fame.\n");
    }
}

/* ============================================================
   UTILITAS STRING
   ============================================================ */
void to_upper_str(char *s) {
    while (*s != '\0') {
        *s = toupper((unsigned char) *s);
        s++;
    }
}
