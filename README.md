# Báo cáo Bài tập lớn: Hệ thống Quản lý Nhân viên

## Thông tin sinh viên
- **Họ và tên**: Ngô Mạnh Linh
- **Mã sinh viên**: 20234019
- **Họ và tên**: Nguyễn Đức Long
- **Mã sinh viên**: 202340
- **Môn học**: [Tên môn học]
- **Giảng viên hướng dẫn**: [Tên giảng viên]

## I. Mục tiêu bài tập lớn
Xây dựng một chương trình quản lý nhân viên cho công ty sử dụng ngôn ngữ C, hỗ trợ các chức năng như check-in/check-out, quản lý thông tin nhân viên, phòng ban, và sắp xếp danh sách nhân viên theo các tiêu chí khác nhau. Chương trình sử dụng danh sách liên kết đơn để tổ chức dữ liệu và đảm bảo quản lý bộ nhớ hiệu quả.

## II. Mô tả chương trình
Hệ thống được thiết kế với hai chế độ sử dụng chính:
1. **Chế độ Nhân viên**:
   - Check-in và check-out.
   - Xem thông tin cá nhân của nhân viên (tên, ID, phòng ban, lương, số ngày công, trạng thái).
2. **Chế độ Quản lý**:
   - Xem danh sách nhân viên và thông tin phòng ban.
   - Thêm, xóa, sửa thông tin nhân viên.
   - Sắp xếp danh sách nhân viên theo lương hoặc số ngày công.

Chương trình sử dụng danh sách liên kết đơn để lưu trữ dữ liệu và cung cấp giao diện dòng lệnh đơn giản, dễ sử dụng.

## III. Cấu trúc dữ liệu
Dữ liệu được tổ chức dưới dạng danh sách liên kết đơn với ba cấu trúc chính:

### 1. Cấu trúc `Staff`
Lưu trữ thông tin của một nhân viên:
```c
struct Staff {
    char name[100];           // Tên nhân viên
    char staff_id[100];       // Mã nhân viên
    struct Room* room;        // Con trỏ đến phòng ban
    char position[100];       // Vị trí công việc
    int salary;               // Lương
    int total_working_days;   // Số ngày công
    int status;               // Trạng thái check-in
    struct Staff* next;       // Con trỏ đến nhân viên tiếp theo
};
```

### 2. Cấu trúc `Room`
Lưu trữ thông tin của một phòng ban:

```c
struct Room {
    char name[100];           // Tên phòng ban
    int total_staff;          // Tổng số nhân viên
    struct Staff* list_staff; // Danh sách liên kết nhân viên
    struct Room* next;        // Con trỏ đến phòng ban tiếp theo
};
```

### 2. Cấu trúc `Company`
Lưu trữ thông tin công ty:

```c
struct Company {
    char name[100];           // Tên công ty
    struct Room* list_room;   // Danh sách liên kết phòng ban
};
```

### Mô tả mối quan hệ:
- Mỗi Company chứa một danh sách liên kết các Room.
- Mỗi Room chứa một danh sách liên kết các Staff.
- Mỗi Staff có con trỏ room trỏ đến Room mà nhân viên đó thuộc về, đảm bảo liên kết giữa nhân viên và phòng ban.

## IV. Chức năng chính

### 1. Check-in (lựa chọn 1 trong Page Staff)
- **Mô tả**: Cho phép nhân viên check-in để ghi nhận trạng thái làm việc.
- **Cách hoạt động**:
  1. Nhập ID nhân viên thông qua hàm `nhap_chuoi`.
  2. Duyệt qua danh sách phòng ban (`list_room`) và danh sách nhân viên (`list_staff`) để tìm nhân viên có ID khớp.
  3. Kiểm tra trạng thái (`status`):
     - Nếu `status = 0` (chưa check-in), đặt `status = 1` và thông báo check-in thành công.
     - Nếu `status = 1` (đã check-in), hiển thị thông báo "Nhân viên đã check-in rồi".
  4. Nếu không tìm thấy ID, thông báo "Không tìm thấy nhân viên".
- **Độ phức tạp**: O(n), với n là tổng số nhân viên (do cần duyệt danh sách để tìm ID).

- **Code**:
```c
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
```

### 2. Check-out (lựa chọn 2 trong Page Staff)
- **Mô tả**: Cho phép nhân viên check-out để kết thúc trạng thái làm việc và tăng số ngày công.
- **Cách hoạt động**:
  1. Nhập ID nhân viên thông qua hàm `nhap_chuoi`.
  2. Duyệt qua danh sách phòng ban và nhân viên để tìm nhân viên có ID khớp.
  3. Kiểm tra trạng thái (`status`):
     - Nếu `status = 1` (đã check-in), đặt `status = 0`, tăng `total_working_days` lên 1, và thông báo check-out thành công.
     - Nếu `status = 0` (chưa check-in), hiển thị thông báo "Nhân viên chưa check-in nên không thể check-out".
  4. Nếu không tìm thấy ID, thông báo "Không tìm thấy nhân viên".
- **Độ phức tạp**: O(n), với n là tổng số nhân viên.

- **Code**:
```c
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
```

### 3. Xem thông tin cá nhân (lựa chọn 3 trong Page Staff)
- **Mô tả**: Hiển thị thông tin chi tiết của một nhân viên dựa trên ID.
- **Cách hoạt động**:
  1. Nhập ID nhân viên thông qua hàm `nhap_chuoi`.
  2. Duyệt qua danh sách phòng ban và nhân viên để tìm nhân viên có ID khớp.
  3. Nếu tìm thấy, in thông tin nhân viên bao gồm: tên, ID, phòng ban (`room->name`), lương, tổng số ngày công, trạng thái (đang làm việc hoặc không).
  4. Nếu không tìm thấy ID, thông báo "Không tìm thấy nhân viên".
- **Độ phức tạp**: O(n), với n là tổng số nhân viên.
- **Hàm liên quan**: `staff_page`, `nhap_chuoi`.

- **Code**:
```c
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
```

### 4. Xem thông tin nhân viên (lựa chọn 1 trong Page Manager)
- **Mô tả**: Hiển thị danh sách tất cả nhân viên trong công ty dưới dạng bảng.
- **Cách hoạt động**:
  1. Duyệt qua tất cả phòng ban (`list_room`) và danh sách nhân viên (`list_staff`) của từng phòng.
  2. In bảng thông tin với các cột: Tên nhân viên, ID, Phòng ban, Lương, Số ngày công.
- **Độ phức tạp**: O(n), với n là tổng số nhân viên.
- **Hàm liên quan**: `manager_page`.

- **Code**:
```c
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
```

### 5. Xem thông tin phòng ban (lựa chọn 2 trong Page Manager)
- **Mô tả**: Hiển thị thông tin chi tiết của tất cả phòng ban, bao gồm trưởng phòng, tổng số nhân viên, và tổng lương.
- **Cách hoạt động**:
  1. Duyệt qua danh sách phòng ban (`list_room`).
  2. Với mỗi phòng ban:
     - Tính tổng số nhân viên bằng cách đếm các node trong `list_staff` (bỏ qua node đầu là node dummy).
     - Tính tổng lương bằng cách cộng `salary` của tất cả nhân viên trong phòng.
     - Lấy tên trưởng phòng từ nhân viên đầu tiên trong `list_staff->next`.
     - In thông tin: tên phòng, trưởng phòng, tổng số nhân viên, tổng lương.
- **Độ phức tạp**: O(n + m), với n là số nhân viên và m là số phòng ban.
- **Hàm liên quan**: `manager_page`.

- **Code**:
```c
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
```

### 6. Thêm/Sửa/Xóa nhân viên
- **Mô tả**: Cho phép quản lý thêm, sửa, hoặc xóa thông tin nhân viên trong công ty.
- **Cách hoạt động**:
  - **Thêm nhân viên** (lựa chọn 3 trong Page Manager):
    1. Nhập tên phòng ban, kiểm tra xem phòng có tồn tại trong `list_room`.
    2. Nhập thông tin nhân viên: tên, ID, lương (sử dụng `nhap_chuoi` và `nhap_so_nguyen`).
    3. Tạo node `Staff` mới, gán thông tin và liên kết với phòng ban tương ứng.
    4. Thêm node vào cuối danh sách `list_staff` của phòng, tăng `total_staff`.
    5. Thông báo thêm thành công.
    - **Độ phức tạp**: O(m) để tìm phòng ban, O(1) để thêm nhân viên.
    - **Code**:
    ```c
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
    ```
  - **Sửa thông tin nhân viên** (lựa chọn 5 trong Page Manager):
    1. Nhập ID nhân viên, tìm nhân viên trong danh sách phòng ban.
    2. Hiển thị menu sửa (1: tên, 2: ID, 3: phòng ban, 4: lương, 5: thoát).
    3. Thực hiện sửa:
       - **Tên**: Cập nhật `name` bằng chuỗi mới.
       - **ID**: Nhập ID mới, kiểm tra không trùng với ID khác trong công ty, cập nhật `staff_id`.
       - **Phòng ban**: Nhập tên phòng mới, kiểm tra tồn tại, chuyển nhân viên sang danh sách `list_staff` của phòng mới, cập nhật `total_staff`.
       - **Lương**: Nhập lương mới, cập nhật `salary`.
    4. Thông báo cập nhật thành công hoặc lỗi nếu không tìm thấy nhân viên.
    - **Độ phức tạp**: O(n) để tìm nhân viên, O(n) để kiểm tra trùng ID.
    - **Code**:
    ```c
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
                                printf("Da cap nhat luong moi cho nhan vien %s!\n",     staff_id);
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
    ```
  - **Xóa nhân viên** (lựa chọn 4 trong Page Manager):
    1. Nhập ID nhân viên, tìm trong danh sách phòng ban.
    2. Nếu tìm thấy, xóa node khỏi `list_staff` của phòng, giảm `total_staff`.
    3. Thông báo xóa thành công hoặc lỗi nếu không tìm thấy.
    - **Độ phức tạp**: O(n) để tìm và xóa nhân viên.
    - **Code**:
    ```c
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
    ```

### 7. Sắp xếp danh sách nhân viên theo lương/ngày công
- **Mô tả**: Sắp xếp và hiển thị danh sách nhân viên theo lương (tăng dần) hoặc số ngày công (tăng dần).
- **Cách hoạt động**:
  - **Sắp xếp theo lương** (lựa chọn 6 trong Page Manager):
    1. Tạo danh sách liên kết mới (`list_all_staff`) để lưu bản sao nhân viên.
    2. Duyệt qua tất cả phòng ban và nhân viên, sao chép thông tin vào node mới.
    3. Chèn từng node vào danh sách liên kết theo thứ tự lương tăng dần (hàm `insert_by_salary`).
    4. In bảng thông tin của danh sách đã sắp xếp (tên, ID, phòng ban, lương, ngày công).
    5. Giải phóng bộ nhớ của danh sách tạm.
  - **Sắp xếp theo ngày công** (lựa chọn 7 trong Page Manager):
    1. Tương tự lựa chọn 6, nhưng sử dụng hàm `insert_by_days` để chèn theo thứ tự ngày công tăng dần.
  - **Chi tiết hàm chèn** (`insert_by_salary`/`insert_by_days`):
    - Duyệt danh sách liên kết, tìm vị trí chèn sao cho lương (hoặc ngày công) của node hiện tại nhỏ hơn node mới.
    - Chèn node mới vào vị trí thích hợp, duy trì thứ tự tăng dần.
  - **Độ phức tạp**: O(n²) trong trường hợp xấu nhất do chèn vào danh sách liên kết.
      
- **Code**:
```c
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
```






