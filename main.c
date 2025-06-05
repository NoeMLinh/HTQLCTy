#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ================
//    Structure
// ================

struct Staff {
    char name[100];
    char staff_id[100];
    struct Room* room;
    char position[100];
    int salary;
    int total_working_days;
    int status;
    
    struct Staff* next;
};

struct Room {
    char name[100];
    int total_staff;
    struct Staff* list_staff;
    
    struct Room* next;
};

struct Company {
    char name[100];
    struct Room* list_room;
};

// ================
//   Khai báo hàm
// ================

void nhap_so_nguyen(int* soKetQua);
void nhap_chuoi(char* ketQua);
void interface_0(char name_company[100]);
void init_structure(struct Company** company, struct Room** list_room, struct Staff** list_staff);
void init_data(struct Company* company, struct Room* list_room, struct Staff* list_staff);
void interface_staff(void);
void staff_page(struct Company* company);
void interface_manager(void);
void insert_by_salary(struct Staff* head, struct Staff* new_staff);
void insert_by_days(struct Staff* head, struct Staff* new_staff);
void manager_page(struct Company* company);
void free_staff_list(struct Staff* head);
void free_room_list(struct Room* head);
void cleanup_all_memory(struct Company** company, struct Room** list_room, struct Staff** list_staff);

// ================
//       MAIN
// ================

struct Company* company = NULL;
struct Room* list_room = NULL;
struct Staff* list_staff = NULL;

int main(void) {
    init_structure(&company, &list_room, &list_staff);
    init_data(company, list_room, list_staff);
    
    int option = 0;
    char name_company[100];
    strncpy(name_company, company->name, 99);
    name_company[sizeof(name_company) - 1] = '\0';
    
    while (1) {
        interface_0(name_company);
        nhap_so_nguyen(&option);
        switch (option) {
            case 1:
                printf("\n");
                staff_page(company);
                break;
            case 2:
                manager_page(company);
                break;
            case 3:
                printf("Bai bai hehehe\n");
                break;
            default:
                break;
        }
        if (option == 3) {
            break;
        }
    }
    cleanup_all_memory(&company, &list_room, &list_staff);
    return 0;
}

// ================
//     Function
// ================

void nhap_so_nguyen(int* soKetQua) {
    int ketQua;
    char kyTuDu;
    
    while (1) {
        if (scanf("%d%c", &ketQua, &kyTuDu) == 2 && kyTuDu == '\n') {
            *soKetQua = ketQua;
            break;
        } else {
            printf("❌ Sai định dạng, vui lòng nhập lại: ");
            while (getchar() != '\n');
        }
    }
}

void nhap_chuoi(char* ketQua) {
    int hopLe;
    int i;
    char c = '\0';
    do {
        hopLe = 0;
        i = 0;
        while (i < 99) {
            c = getchar();
            if (c == '\n') break;
            ketQua[i++] = c;
        }
        ketQua[i] = '\0';
        if (c != '\n') {
            while ((c = getchar()) != '\n' && c != EOF);
        }
        for (int j = 0; j < i; j++) {
            if (ketQua[j] != ' ') {
                hopLe = 1;
                break;
            }
        }
        if (!hopLe) {
            printf("❌ Chuỗi không được để trống. Nhập lại: ");
        }
    } while (!hopLe);
}

void interface_0(char name_company[100]) {
    printf("\n===== He thong quan ly nhan vien =====\n");
    printf("    ===== cua cong ty %s =====\n", name_company);
    printf(" 1. Nhan vien\n");
    printf(" 2. Quan ly\n");
    printf(" 3. Thoat\n");
    printf("Nhập lựa chọn: ");
}

void init_structure(struct Company** company, struct Room** list_room, struct Staff** list_staff) {
    
    *company = (struct Company*)malloc(sizeof(struct Company));
    strncpy((*company)->name, "LONG34", 99);
    (*company)->name[sizeof((*company)->name) - 1] = '\0';
    (*company)->list_room = NULL;
    
    *list_room = (struct Room*)malloc(sizeof(struct Room));
    (*list_room)->name[0] = '\0';
    (*list_room)->total_staff = 0;
    (*list_room)->list_staff = NULL;
    (*list_room)->next = NULL;
    
    *list_staff = (struct Staff*)malloc(sizeof(struct Staff));
    (*list_staff)->name[0] = '\0';
    (*list_staff)->staff_id[0] = '\0';
    (*list_staff)->room = NULL;
    (*list_staff)->position[0] = '\0';
    (*list_staff)->salary = 0;
    (*list_staff)->total_working_days = 0;
    (*list_staff)->status = 0;
    (*list_staff)->next = NULL;
}

void init_data(struct Company* company, struct Room* list_room, struct Staff* list_staff) {
    char roomNames[3][100] = {"Ban hang", "San xuat", "Kiem tra SP"};
    int staffCount[3] = {4, 4, 4};
    char positions[12][100] = {
        "Truong phong", "Nhan vien chinh thuc", "Nhan vien chinh thuc", "Thuc tap",
        "Truong phong", "Nhan vien chinh thuc", "Nhan vien chinh thuc", "Thuc tap",
        "Truong phong", "Nhan vien chinh thuc", "Nhan vien chinh thuc", "Thuc tap"
    };

    struct Room* roomTail = list_room;
    int staffIndex = 0;

    char staffNames[12][100] = {
        "Nguyen Van A", "Le Thi B", "Tran Van C", "Pham Thi D",
        "Hoang Van E", "Nguyen Van F", "Le Thi G", "Tran Van H",
        "Pham Thi I", "Hoang Van J", "Nguyen Van K", "Le Thi L"
    };
    char staffIDs[12][20] = {
        "nv001", "nv002", "nv003", "nv004",
        "nv005", "nv006", "nv007", "nv008",
        "nv009", "nv010", "nv011", "nv012"
    };
    int salaries[12] = {
        16000000, 11000000, 12000000, 7000000,
        14000000, 10500000, 11500000, 8500000,
        18500000, 14500000, 15000000, 7500000
    };
    int days[12] = {
        20, 22, 21, 23,
        20, 19, 21, 16,
        22, 23, 21, 28
    };

    struct Staff* globalStaffTail = list_staff;
    for (int i = 0; i < 3; i++) {
        struct Room* newRoom = (struct Room*)malloc(sizeof(struct Room));
        strncpy(newRoom->name, roomNames[i], sizeof(newRoom->name) - 1);
        newRoom->name[sizeof(newRoom->name) - 1] = '\0';
        newRoom->total_staff = staffCount[i];
        newRoom->list_staff = (struct Staff*)malloc(sizeof(struct Staff));
        newRoom->list_staff->next = NULL;
        newRoom->list_staff->name[0] = '\0';
        newRoom->next = NULL;

        struct Staff* roomStaffTail = newRoom->list_staff;
        for (int j = 0; j < staffCount[i]; j++) {
            struct Staff* newStaff = (struct Staff*)malloc(sizeof(struct Staff));
            strncpy(newStaff->name, staffNames[staffIndex], sizeof(newStaff->name) - 1);
            newStaff->name[sizeof(newStaff->name) - 1] = '\0';
            strncpy(newStaff->staff_id, staffIDs[staffIndex], sizeof(newStaff->staff_id) - 1);
            newStaff->staff_id[sizeof(newStaff->staff_id) - 1] = '\0';
            newStaff->salary = salaries[staffIndex];
            newStaff->total_working_days = days[staffIndex];
            newStaff->status = 0;
            newStaff->room = newRoom;
            strncpy(newStaff->position, positions[staffIndex], sizeof(newStaff->position) - 1);
            newStaff->position[sizeof(newStaff->position) - 1] = '\0';
            newStaff->next = NULL;
            roomStaffTail->next = newStaff;
            roomStaffTail = newStaff;

            struct Staff* globalStaff = (struct Staff*)malloc(sizeof(struct Staff));
            memcpy(globalStaff, newStaff, sizeof(struct Staff));
            globalStaff->next = NULL;
            globalStaff->room = newRoom;
            globalStaffTail->next = globalStaff;
            globalStaffTail = globalStaff;
            staffIndex++;
        }
        roomTail->next = newRoom;
        roomTail = newRoom;
    }
    company->list_room = list_room->next;
}

void free_staff_list(struct Staff* head) {
    struct Staff* current = head;
    struct Staff* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void free_room_list(struct Room* head) {
    struct Room* current = head;
    struct Room* next;
    
    while (current != NULL) {
        next = current->next;
        if (current->list_staff != NULL) {
            free_staff_list(current->list_staff);
        }
        free(current);
        current = next;
    }
}

void cleanup_all_memory(struct Company** company, struct Room** list_room, struct Staff** list_staff) {
    if (*list_staff != NULL) {
        free_staff_list(*list_staff);
        *list_staff = NULL;
    }
    if (*list_room != NULL) {
        free_room_list(*list_room);
        *list_room = NULL;
    }
    if (*company != NULL) {
        free(*company);
        *company = NULL;
    }
    printf("✅ Đã giải phóng toàn bộ bộ nhớ thành công!\n");
}

void interface_staff(void) {
    printf("===== Chon thao tac ban muon thuc hien =====\n");
    printf("  1. Check in\n");
    printf("  2. Check out\n");
    printf("  3. Xem thong tin nhan vien\n");
    printf("  4. Thoat\n");
}

void staff_page(struct Company* company) {
    interface_staff();
    int choice = 0;
    char staff_id[100];
    
    while (1) {
        printf("Nhap lua chon: ");
        nhap_so_nguyen(&choice);
        if (choice >= 1 && choice <= 4) {
            break;
        }
        printf("Lua chon khong hop le, vui long nhap lai!\n");
    }

    if (choice == 4) {
        return;
    }

    struct Room* room = company->list_room;
    int found = 0;
    printf("Nhap ID nhan vien: ");
    nhap_chuoi(staff_id);

    while (room != NULL) {
        struct Staff* staff = room->list_staff->next;
        // kiểm tra xem id có trong danh sách nhân viên của công ty không, truy cập company, duyệt qua từng room->list_staff
        while (staff != NULL) {
            if (strcmp(staff->staff_id, staff_id) == 0) {
                found = 1;
                // nếu tìm thấy thì bắt đầu thực hiện
                switch (choice) {
                    case 1: // check in
                        // kiểm tra status, nếu = 0 thì chuyển sang 1, nếu = 1 thì thông báo đã check in
                        if (staff->status == 1) {
                            printf("===============================\n");
                            printf("Nhan vien đa check-in roi.\n");
                            printf("===============================\n");
                        } else {
                            staff->status = 1;
                            printf("===============================\n");
                            printf("Check-in thanh cong cho nhan vien %s.\n", staff->name);
                            printf("===============================\n");
                        }
                        break;
                    case 2: // check out
                        // kiểm tra status, nếu đang bằng 1 thì chuyển về 0 và thông báo checkout thành công, nếu đang bằng 0 thì báo nhân viên này chưa check in
                        if (staff->status == 0) {
                            printf("===============================\n");
                            printf("Nhan vien chua check-in nen khong the check-out.\n");
                            printf("===============================\n");
                        } else {
                            staff->status = 0;
                            staff->total_working_days += 1;
                            printf("===============================\n");
                            printf("Check-out thanh cong cho nhan vien %s.\n", staff->name);
                            printf("===============================\n");
                        }
                        break;
                    case 3: // xem thông tin
                        // in ra màn hình những thông tin như name, staff_id, room, salary, total_working_days, total_products
                        printf("===== THONG TIN NHAN VIEN =====\n");
                        printf("  - Ten: %s\n", staff->name);
                        printf("  - ID: %s\n", staff->staff_id);
                        printf("  - Phong: %s\n", room->name);
                        printf("  - Luong: %d\n", staff->salary);
                        printf("  - Tong ngay lam viec: %d\n", staff->total_working_days);
                        printf("  - Trạng thái: %s\n", staff->status == 1 ? "Dang lam viec" : "Dang khong lam viec");
                        printf("===============================\n");
                        break;
                }
                break;
            }
            staff = staff->next;
        }
        if (found) {
            break;
        }
        room = room->next;
    }
    // nếu không tìm thấy thì thông báo không có trong danh sách
    if (!found) {
        printf("===============================\n");
        printf("Khong tim thay nhan vien voi ID \"%s\" trong cong ty.\n", staff_id);
        printf("===============================\n");
    }
}

void interface_manager(void) {
    printf("\n===== Chon thao tac ban muon thuc hien =====\n");
    printf("  1. Xem thong tin nhan vien\n");
    printf("  2. Xem thong tin phong ban\n");
    printf("  3. Them nhan vien\n");
    printf("  4. Xoa nhan vien\n");
    printf("  5. Sua thong tin nhan vien\n");
    printf("  6. Sap xep danh sach nhan vien theo luong\n");
    printf("  7. Sap xep danh sach nhan vien theo ngay cong\n");
    printf("  8. Thoat\n");
}

void insert_by_salary(struct Staff* head, struct Staff* new_staff) {
    struct Staff* prev = head;
    struct Staff* curr = head->next;

    while (curr != NULL && curr->salary < new_staff->salary) {
        prev = curr;
        curr = curr->next;
    }

    new_staff->next = curr;
    prev->next = new_staff;
}

void insert_by_days(struct Staff* head, struct Staff* new_staff) {
    struct Staff* prev = head;
    struct Staff* curr = head->next;

    while (curr != NULL && curr->total_working_days < new_staff->total_working_days) {
        prev = curr;
        curr = curr->next;
    }

    new_staff->next = curr;
    prev->next = new_staff;
}

void manager_page(struct Company* company) {
    interface_manager();
    int choice = 0;
    
    while (1) {
        printf("Nhap lua chon: ");
        nhap_so_nguyen(&choice);
        if (choice >= 1 && choice <= 8) {
            break;
        }
        printf("Lua chon khong hop le, vui long nhap lai!\n");
    }

    if (choice == 8) {
        return;
    }
    
    switch (choice) {
        case 1: {
            printf("\n");
            printf("+---------------+-------+-------------+----------+--------------+\n");
            printf("| Ten Nhan Vien |  ID   |  Phong Ban  |  Luong   | So ngay cong |\n");
            printf("+---------------+-------+-------------+----------+--------------+\n");
            struct Room* room = company->list_room;
            while (room != NULL) {
                struct Staff* staff = room->list_staff->next;
                while (staff != NULL) {
                    printf("| %-13s | %-5s | %-11s | %-8d |      %-7d |\n",
                           staff->name,
                           staff->staff_id,
                           room->name,
                           staff->salary,
                           staff->total_working_days);
                    staff = staff->next;
                }
                room = room->next;
            }
            printf("+---------------+-------+-------------+----------+--------------+\n");
            break;
        }
        case 2: {
            printf("\n===== THONG TIN CAC PHONG BAN =====\n");
            struct Room* room = company->list_room;
            while (room != NULL) {
                int staff_count = 0;
                int total_product = 0;
                int total_salary = 0;
                
                struct Staff* staff = room->list_staff;
                if (staff != NULL) staff = staff->next;

                while (staff != NULL) {
                    staff_count++;
                    total_salary += staff->salary;
                    staff = staff->next;
                }
                
                printf("Phong %s\n", room->name);
                printf("Truong phong      : %s\n", room->list_staff->next->name);
                printf("Tong so nhan vien : %d\n", staff_count);
                printf("Tong so san pham  : %d\n", total_product);
                printf("Tong luong        : %d\n", total_salary);
                if (room->next != NULL) {
                    printf("\n");
                }
                room = room->next;
            }
            printf("===================================\n");
            break;
        }
        case 3: { // thêm nhân viên
            char room_name[100] = "";
            char name[100] = "";
            char staff_id[100] = "";
            int salary = 0;

            struct Room* selected_room = NULL;

            while (1) {
                printf("Nhan vien moi lam viec o phong nao: ");
                nhap_chuoi(room_name);

                struct Room* r = company->list_room;
                while (r != NULL) {
                    if (strcmp(r->name, room_name) == 0) {
                        selected_room = r;
                        break;
                    }
                    r = r->next;
                }

                if (selected_room != NULL) break;
                printf("Phong khong ton tai. Vui long nhap lai!\n");
            }

            while (1) {
                printf("Nhap ten nhan vien: ");
                nhap_chuoi(name);
                if (strlen(name) > 0) break;
                printf("Ten khong duoc de trong. Vui long nhap lai!\n");
            }

            while (1) {
                printf("Nhap ID nhan vien: ");
                nhap_chuoi(staff_id);
                if (strlen(staff_id) > 0) break;
                printf("ID khong duoc de trong. Vui long nhap lai!\n");
            }

            while (1) {
                printf("Nhap luong co ban: ");
                nhap_so_nguyen(&salary);
                if (salary > 0) break;
                printf("Luong phai lon hon 0. Vui long nhap lai!\n");
            }

            struct Staff* new_staff = (struct Staff*)malloc(sizeof(struct Staff));
            strcpy(new_staff->name, name);
            strcpy(new_staff->staff_id, staff_id);
            new_staff->room = selected_room;
            new_staff->salary = salary;
            new_staff->total_working_days = 0;
            new_staff->status = 0;
            new_staff->next = NULL;

            struct Staff* last = selected_room->list_staff;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = new_staff;
            selected_room->total_staff++;

            printf("Them nhan vien thanh cong!\n\n");
            break;
        }
        case 4: { // Xoá nhân viên
            char staff_id[100];
            printf("Nhap ID nhan vien can xoa: ");
            nhap_chuoi(staff_id);

            struct Room* room = company->list_room;
            int found = 0;

            while (room != NULL) {
                struct Staff* prev = room->list_staff;
                struct Staff* curr = prev->next;

                while (curr != NULL) {
                    if (strcmp(curr->staff_id, staff_id) == 0) {
                        prev->next = curr->next;
                        free(curr);
                        printf("Da xoa nhan vien co ID: %s trong phong %s\n", staff_id, room->name);
                        found = 1;
                        break;
                    }
                    prev = curr;
                    curr = curr->next;
                }
                if (found) break;
                room = room->next;
            }

            if (!found) {
                printf("Khong tim thay nhan vien co ID: %s\n", staff_id);
            }
            return;
        }
        case 5: { // sửa thông tin nhân viên
            char staff_id[100];
            printf("Nhap ID nhan vien can sua thong tin: ");
            nhap_chuoi(staff_id);

            struct Room* room = company->list_room;
            int found = 0;

            while (room != NULL) {
                struct Staff* ptr = room->list_staff->next;
                while (ptr != NULL) {
                    if (strcmp(ptr->staff_id, staff_id) == 0) {
                        found = 1;
                        int edit_choice = 0;
                        while (1) {
                            printf("\n===== Chon thong tin muon sua =====\n");
                            printf("  1. Ten\n");
                            printf("  2. ID\n");
                            printf("  3. Phong ban\n");
                            printf("  4. Luong\n");
                            printf("  5. Thoat\n");
                            printf("Nhap lua chon: ");
                            nhap_so_nguyen(&edit_choice);

                            switch (edit_choice) {
                                case 1:
                                    printf("Nhap ten moi: ");
                                    nhap_chuoi(ptr->name);
                                    printf("Da cap nhat ten moi!\n");
                                    break;
                                case 2: {
                                    char new_id[100];
                                    int is_duplicate = 0;

                                    while (1) {
                                        printf("Nhap ID moi: ");
                                        nhap_chuoi(new_id);
                                        struct Room* r = company->list_room;
                                        while (r != NULL) {
                                            struct Staff* s = r->list_staff->next;
                                            while (s != NULL) {
                                                if (strcmp(s->staff_id, new_id) == 0) {
                                                    is_duplicate = 1;
                                                    break;
                                                }
                                                s = s->next;
                                            }
                                            if (is_duplicate) break;
                                            r = r->next;
                                        }
                                        if (is_duplicate) {
                                            printf("ID da ton tai, vui long nhap ID khac.\n");
                                            is_duplicate = 0;
                                        } else {
                                            strcpy(ptr->staff_id, new_id);
                                            printf("Da cap nhat ID moi!\n");
                                            break;
                                        }
                                    }
                                    break;
                                }
                                case 3: { // Sửa phòng ban
                                    char new_room_name[100] = "";
                                    struct Room* new_room = NULL;

                                    while (1) {
                                        printf("Nhap ten phong moi (Ban hang/San xuat/Kiem tra SP): ");
                                        nhap_chuoi(new_room_name);
                                        struct Room* temp = company->list_room;
                                        while (temp != NULL) {
                                            if (strcmp(temp->name, new_room_name) == 0) {
                                                new_room = temp;
                                                break;
                                            }
                                            temp = temp->next;
                                        }
                                        if (new_room != NULL) break;
                                        printf("Phong ban khong ton tai, vui long nhap lai!\n");
                                    }

                                    if (ptr->room != new_room) {
                                        struct Staff* prev = room->list_staff;
                                        while (prev->next != NULL && prev->next != ptr) {
                                            prev = prev->next;
                                        }
                                        if (prev->next == ptr) {
                                            prev->next = ptr->next;
                                            room->total_staff--;
                                        }

                                        struct Staff* tail = new_room->list_staff;
                                        while (tail->next != NULL) {
                                            tail = tail->next;
                                        }
                                        tail->next = ptr;
                                        ptr->next = NULL;
                                        new_room->total_staff++;

                                        ptr->room = new_room;
                                        printf("Da chuyen nhan vien sang phong %s\n", new_room->name);
                                    } else {
                                        printf("Nhan vien da o phong nay roi.\n");
                                    }
                                    break;
                                }
                                case 4:
                                    printf("Nhap luong moi: ");
                                    nhap_so_nguyen(&ptr->salary);
                                    printf("Da cap nhat luong moi cho nhan vien %s!\n", staff_id);
                                    break;
                                case 5:
                                    return;
                                default:
                                    printf("Lua chon khong hop le, vui long chon lai.\n");
                            }
                            break;
                        }
                    }
                    ptr = ptr->next;
                }
                if (found) break;
                room = room->next;
            }
            if (!found) {
                printf("Khong tim thay nhan vien co ID: %s\n", staff_id);
            }
            return;
        }
        case 6: { // sắp xếp danh sách nhân viên theo thứ tự lương
            struct Staff* list_all_staff = (struct Staff*)malloc(sizeof(struct Staff));
            list_all_staff->next = NULL;

            struct Room* room = company->list_room;
            while (room != NULL) {
                struct Staff* staff = room->list_staff->next;
                while (staff != NULL) {
                    struct Staff* new_node = (struct Staff*)malloc(sizeof(struct Staff));
                    *new_node = *staff;
                    new_node->next = NULL;
                    insert_by_salary(list_all_staff, new_node);
                    staff = staff->next;
                }
                room = room->next;
            }

            printf("+---------------+-------+-------------+----------+--------------+\n");
            printf("| Ten Nhan Vien |  ID   |  Phong Ban  |  Luong   | So ngay cong |\n");
            printf("+---------------+-------+-------------+----------+--------------+\n");
            struct Staff* ptr = list_all_staff->next;
            while (ptr != NULL) {
                printf("| %-13s | %-5s | %-11s | %-8d |      %-7d |\n",
                       ptr->name,
                       ptr->staff_id,
                       ptr->room->name,
                       ptr->salary,
                       ptr->total_working_days);
                ptr = ptr->next;
            }
            printf("+---------------+-------+-------------+----------+--------------+\n");
            
            ptr = list_all_staff;
            while (ptr != NULL) {
                struct Staff* tmp = ptr;
                ptr = ptr->next;
                free(tmp);
            }

            return;
        }
        case 7: { // sắp xếp danh sách nhân viên theo thứ ngày công
            struct Staff* list_all_staff = (struct Staff*)malloc(sizeof(struct Staff));
            list_all_staff->next = NULL;

            struct Room* room = company->list_room;
            while (room != NULL) {
                struct Staff* staff = room->list_staff->next;
                while (staff != NULL) {
                    struct Staff* new_node = (struct Staff*)malloc(sizeof(struct Staff));
                    *new_node = *staff;
                    new_node->next = NULL;
                    insert_by_days(list_all_staff, new_node);
                    staff = staff->next;
                }
                room = room->next;
            }

            printf("+---------------+-------+-------------+----------+--------------+\n");
            printf("| Ten Nhan Vien |  ID   |  Phong Ban  |  Luong   | So ngay cong |\n");
            printf("+---------------+-------+-------------+----------+--------------+\n");
            struct Staff* ptr = list_all_staff->next;
            while (ptr != NULL) {
                printf("| %-13s | %-5s | %-11s | %-8d |      %-7d |\n",
                       ptr->name,
                       ptr->staff_id,
                       ptr->room->name,
                       ptr->salary,
                       ptr->total_working_days);
                ptr = ptr->next;
            }
            printf("+---------------+-------+-------------+----------+--------------+\n");
            
            ptr = list_all_staff;
            while (ptr != NULL) {
                struct Staff* tmp = ptr;
                ptr = ptr->next;
                free(tmp);
            }

            return;
        }
        case 8: {
            return;
        }
        default:
            printf("Lua chon khong hop le. Vui long thu lai!\n");
            break;
    }
}

