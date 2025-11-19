#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 200

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char id[7];      // 6 chars + '\0'
    char name[51];
    char gender[6];  // "Nam" / "Nu" etc.
    char phone[16];
    Date dob;
} Student;

void normalize(char *s) {
    for (; *s; ++s) *s = tolower((unsigned char)*s);
}

void printStudent(const Student *s, int index) {
    printf("%-3d %-6s | %-20s | %-5s | %-12s | %02d/%02d/%04d\n",
           index + 1, s->id, s->name, s->gender, s->phone,
           s->dob.day, s->dob.month, s->dob.year);
}

void listStudents(const Student list[], int count) {
	int i;
    if (count == 0) {
        puts("Danh sach rong.");
        return;
    }
    puts("STT MSV    | Ho ten              | GT    | SDT          | Ngay sinh");
    puts("---------------------------------------------------------------------");
    for (i = 0; i < count; ++i) printStudent(&list[i], i);
}

Student inputStudent(void) {
    Student s;
    printf("Ma SV (6 ky tu): ");
    scanf("%6s", s.id); while (getchar() != '\n');
    printf("Ho va ten: ");
    fgets(s.name, sizeof s.name, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Gioi tinh: ");
    fgets(s.gender, sizeof s.gender, stdin);
    s.gender[strcspn(s.gender, "\n")] = 0;
    printf("So dien thoai: ");
    fgets(s.phone, sizeof s.phone, stdin);
    s.phone[strcspn(s.phone, "\n")] = 0;
    printf("Ngay sinh (dd mm yyyy): ");
    scanf("%d %d %d", &s.dob.day, &s.dob.month, &s.dob.year);
    while (getchar() != '\n');
    return s;
}

int findIndexById(const Student list[], int count, const char *id) {
	int i;
    for (i = 0; i < count; ++i)
        if (strcmp(list[i].id, id) == 0) return i;
    return -1;
}

void updateStudent(Student list[], int count) {
    char id[7];
    printf("Nhap ma SV can cap nhat: ");
    scanf("%6s", id); while (getchar() != '\n');

    int idx = findIndexById(list, count, id);
    if (idx == -1) {
        puts("Khong tim thay sinh vien.");
        return;
    }
    printf("Cap nhat ho ten: ");
    fgets(list[idx].name, sizeof list[idx].name, stdin);
    list[idx].name[strcspn(list[idx].name, "\n")] = 0;

    printf("Cap nhat gioi tinh: ");
    fgets(list[idx].gender, sizeof list[idx].gender, stdin);
    list[idx].gender[strcspn(list[idx].gender, "\n")] = 0;

    printf("Cap nhat so dien thoai: ");
    fgets(list[idx].phone, sizeof list[idx].phone, stdin);
    list[idx].phone[strcspn(list[idx].phone, "\n")] = 0;

    printf("Cap nhat ngay sinh (dd mm yyyy): ");
    scanf("%d %d %d", &list[idx].dob.day, &list[idx].dob.month, &list[idx].dob.year);
    while (getchar() != '\n');

    puts("Da cap nhat.");
}

void deleteStudent(Student list[], int *count) {
    char id[7];
    printf("Nhap ma SV can xoa: ");
    scanf("%6s", id); while (getchar() != '\n');
	int i;
    int idx = findIndexById(list, *count, id);
    if (idx == -1) {
        puts("Khong tim thay sinh vien.");
        return;
    }
    for (i = idx; i < *count - 1; ++i) list[i] = list[i + 1];
    --(*count);
    puts("Da xoa sinh vien.");
}

void addStudentFront(Student list[], int *count) {
    if (*count == MAX_STUDENTS) {
        puts("Danh sach day.");
        return;
    }
    Student s = inputStudent();
    int i;
    for (i = *count; i > 0; --i) list[i] = list[i - 1];
    list[0] = s;
    ++(*count);
    puts("Da them sinh vien vao dau mang.");
}

void searchByName(const Student list[], int count) {
	int i;
    char name[51];
    printf("Nhap ten can tim: ");
    fgets(name, sizeof name, stdin);
    name[strcspn(name, "\n")] = 0;

    char target[51];
    strcpy(target, name);
    normalize(target);

    int found = 0;
    for (i = 0; i < count; ++i) {
        char current[51];
        strcpy(current, list[i].name);
        normalize(current);
        if (strstr(current, target)) {
            printStudent(&list[i], i);
            found = 1;
        }
    }
    if (!found) puts("Khong tim thay.");
}

void sortByName(Student list[], int count) {
	int i, j;
    for (i = 0; i < count - 1; ++i)
        for (j = i + 1; j < count; ++j)
            if (strcmp(list[i].name, list[j].name) > 0) {
                Student tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
    puts("Da sap xep theo ten tang dan.");
}

int main(void) {
    Student list[MAX_STUDENTS];
    int count = 0;
    int choice;

    do {
        puts("\n=== MENU ===");
        puts("1. Hien thi danh sach");
        puts("2. Them moi sinh vien (dau mang)");
        puts("3. Cap nhat thong tin (khong doi ma)");
        puts("4. Xoa sinh vien");
        puts("5. Tim kiem theo ten");
        puts("6. Sap xep theo ten A-Z");
        puts("0. Thoat");
        printf("Chon: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: listStudents(list, count); break;
            case 2: addStudentFront(list, &count); break;
            case 3: updateStudent(list, count); break;
            case 4: deleteStudent(list, &count); break;
            case 5: searchByName(list, count); break;
            case 6: sortByName(list, count); break;
            case 0: puts("Tam biet!"); break;
            default: puts("Lua chon khong hop le.");
        }
    } while (choice != 0);

    return 0;
}
