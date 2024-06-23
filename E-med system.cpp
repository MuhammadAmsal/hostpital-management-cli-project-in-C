#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

struct patient {
    int id;
    char patientName[50];
    char patientAddress[50];
    char disease[50];
    char medicines[100];
    char designation[50];
    char date[12];
} p;

struct doctor {
    int id;
    char name[50];
    char address[50];
    char specialize[50];
    char qualification[50];
    char scheduled[50];
    char contact[20];
    char date[12];
} d;

FILE *fp;

void admitPatient();
void patientList();
void dischargePatient();
void addDoctor();
void doctorList();
void updatePatient();
void updateDoctor();

int main() {
    int ch;
    char userInput[100];
    int passwordInput;
    char userName[] = "admin@gmail.com";
    int password = 12345;

    printf("\n\n\n\t\t\t\t\t ################## ADMIN PORTAL ###################\n\n\n");

    printf("\n\t\t\t\t\t\tEnter UserName: ");
    scanf("%s", userInput);
    printf("\n\t\t\t\t\t\tEnter Password: ");
    scanf("%d", &passwordInput);
 
    if (strcmp(userInput, userName) == 0 && passwordInput == password) {
        while (1) {
            system("cls");
             printf("\n\n\t\t\t Made By : Muhammad Wasif BSE-24S-099, Muhammad Amsal BSE-24S-096, Muhammad Saad BSE-24S-089");
            printf("\n\n<============== E-Medical System ============>\n\n");
            printf("1. Admit Patient\n");
            printf("2. Patient List\n");
            printf("3. Discharge Patient\n");
            printf("4. Add Doctor\n");
            printf("5. Doctors List\n");
            printf("6. Update Patient\n");
            printf("7. Update Doctor\n");
            printf("0. Exit\n\n");
            printf("Enter your choice: ");
            
            scanf("%d", &ch);

            switch (ch) {
                case 0:
                    exit(0);

                case 1:
                    admitPatient();
                    break;

                case 2:
                    patientList();
                    break;

                case 3:
                    dischargePatient();
                    break;

                case 4:
                    addDoctor();
                    break;

                case 5:
                    doctorList();
                    break;

                case 6:
                    updatePatient();
                    break;

                case 7:
                    updateDoctor();
                    break;

                default:
                    printf("Invalid Choice...\n\n");
            }
            printf("\n\nPress Any Key To Continue...");
            _getch();  // Use _getch() if you're on Windows and included conio.h
        }
    } else if (passwordInput != password) {
        printf("Incorrect Password");
    } else if (strcmp(userInput, userName) != 0) {
        printf("Incorrect Username");
    }

    return 0;
}

void admitPatient() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(p.date, myDate);

    fp = fopen("patient.txt", "ab");

    printf("Enter Patient id: ");
    scanf("%d", &p.id);

    printf("Enter Patient name: ");
    fflush(stdin);
    fgets(p.patientName, sizeof(p.patientName), stdin);
    p.patientName[strcspn(p.patientName, "\n")] = 0; // Remove newline character

    printf("Enter Patient Address: ");
    fflush(stdin);
    fgets(p.patientAddress, sizeof(p.patientAddress), stdin);
    p.patientAddress[strcspn(p.patientAddress, "\n")] = 0; // Remove newline character

    printf("Enter Patient Disease: ");
    fflush(stdin);
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0; // Remove newline character

    printf("Enter Medicines prescribed: ");
    fflush(stdin);
    fgets(p.medicines, sizeof(p.medicines), stdin);
    p.medicines[strcspn(p.medicines, "\n")] = 0; // Remove newline character

    printf("Enter Designation: ");
    fflush(stdin);
    fgets(p.designation, sizeof(p.designation), stdin);
    p.designation[strcspn(p.designation, "\n")] = 0; // Remove newline character

    printf("\nPatient Added Successfully");

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
}

void patientList() {
    system("cls");
    printf("<============= Patient List ==========>\n\n");
    printf("%-10s %-30s %-30s %-20s %-30s %-30s %s\n", "Id", "Patient Name", "Address", "Disease", "Medicines", "Designation", "Date");
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("patient.txt", "rb");
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        printf("%-10d %-30s %-30s %-20s %-30s %-30s %s\n", p.id, p.patientName, p.patientAddress, p.disease, p.medicines, p.designation, p.date);
    }

    fclose(fp);
}

void dischargePatient() {
    int id, f = 0;
    system("cls");
    printf("<============ Discharge Patient ===========>\n\n");
    printf("Enter Patient id to discharge: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("patient.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (id == p.id) {
            f = 1;
        } else {
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\nPatient Discharged Successfully.");
    } else {
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("patient.txt");
    rename("temp.txt", "patient.txt");
}

void addDoctor() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(d.date, myDate);

    system("cls");
    printf("<== Add Doctor ==>\n\n");

    fp = fopen("doctor.txt", "ab");

    printf("Enter Doctor id: ");
    scanf("%d", &d.id);

    printf("Enter Doctor Name: ");
    fflush(stdin);
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = 0; // Remove newline character

    printf("Enter Doctor Address: ");
    fflush(stdin);
    fgets(d.address, sizeof(d.address), stdin);
    d.address[strcspn(d.address, "\n")] = 0; // Remove newline character

    printf("Doctor Specialize in: ");
    fflush(stdin);
    fgets(d.specialize, sizeof(d.specialize), stdin);
    d.specialize[strcspn(d.specialize, "\n")] = 0; // Remove newline character

    printf("Enter Doctor Qualification: ");
    fflush(stdin);
    fgets(d.qualification, sizeof(d.qualification), stdin);
    d.qualification[strcspn(d.qualification, "\n")] = 0; // Remove newline character

    printf("Enter Doctor Scheduled: ");
    fflush(stdin);
    fgets(d.scheduled, sizeof(d.scheduled), stdin);
    d.scheduled[strcspn(d.scheduled, "\n")] = 0; // Remove newline character

    printf("Enter Doctor Contact: ");
    fflush(stdin);
    fgets(d.contact, sizeof(d.contact), stdin);
    d.contact[strcspn(d.contact, "\n")] = 0; // Remove newline character

    printf("\nDoctor Added Successfully\n");

    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
}

void doctorList() {
    system("cls");
    printf("<=========== Doctor List ==========>\n\n");
    printf("%-10s %-20s %-20s %-20s %-20s %-30s %-20s %s\n", "Id", "Name", "Address", "Specialize", "Qualification", "Scheduled", "Contact", "Date");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("doctor.txt", "rb");
    while (fread(&d, sizeof(d), 1, fp) == 1) {
        printf("%-10d %-20s %-20s %-20s %-20s %-30s %-20s %s\n", d.id, d.name, d.address, d.specialize, d.qualification, d.scheduled, d.contact, d.date);
    }

    fclose(fp);
}

void updatePatient() {
    int id, found = 0;
    printf("Enter Patient ID to update: ");
    scanf("%d", &id);

    fp = fopen("patient.txt", "rb+");
    while (fread(&p, sizeof(p), 1, fp) == 1) {
        if (id == p.id) {
            found = 1;
            printf("Enter Updated Patient name: ");
            fflush(stdin);
            fgets(p.patientName, sizeof(p.patientName), stdin);
            p.patientName[strcspn(p.patientName, "\n")] = 0; // Remove newline character

            printf("Enter Updated Patient Address: ");
            fflush(stdin);
            fgets(p.patientAddress, sizeof(p.patientAddress), stdin);
            p.patientAddress[strcspn(p.patientAddress, "\n")] = 0; // Remove newline character

            printf("Enter Updated Patient Disease: ");
            fflush(stdin);
            fgets(p.disease, sizeof(p.disease), stdin);
            p.disease[strcspn(p.disease, "\n")] = 0; // Remove newline character

            printf("Enter Updated Medicines prescribed: ");
            fflush(stdin);
            fgets(p.medicines, sizeof(p.medicines), stdin);
            p.medicines[strcspn(p.medicines, "\n")] = 0; // Remove newline character

            printf("Enter Updated Designation: ");
            fflush(stdin);
            fgets(p.designation, sizeof(p.designation), stdin);
            p.designation[strcspn(p.designation, "\n")] = 0; // Remove newline character

            fseek(fp, -sizeof(p), SEEK_CUR); // Move the file pointer back
            fwrite(&p, sizeof(p), 1, fp);
            break; // No need to continue looping
        }
    }
    fclose(fp);

    if (found == 0) {
        printf("Patient with ID %d not found.\n", id);
    } else {
        printf("Patient details updated successfully.\n");
    }
}

void updateDoctor() {
    int id, found = 0;
    printf("Enter Doctor ID to update: ");
    scanf("%d", &id);

    fp = fopen("doctor.txt", "rb+");
    while (fread(&d, sizeof(d), 1, fp) == 1) {
        if (id == d.id) {
            found = 1;
            printf("Enter Updated Doctor Name: ");
            fflush(stdin);
            fgets(d.name, sizeof(d.name), stdin);
            d.name[strcspn(d.name, "\n")] = 0; // Remove newline character

            printf("Enter Updated Doctor Address: ");
            fflush(stdin);
            fgets(d.address, sizeof(d.address), stdin);
            d.address[strcspn(d.address, "\n")] = 0; // Remove newline character

            printf("Enter Updated Doctor Specialize in: ");
            fflush(stdin);
            fgets(d.specialize, sizeof(d.specialize), stdin);
            d.specialize[strcspn(d.specialize, "\n")] = 0; // Remove newline character

            printf("Enter Updated Doctor Qualification: ");
            fflush(stdin);
            fgets(d.qualification, sizeof(d.qualification), stdin);
            d.qualification[strcspn(d.qualification, "\n")] = 0; // Remove newline character

            printf("Enter Updated Doctor Scheduled: ");
            fflush(stdin);
            fgets(d.scheduled, sizeof(d.scheduled), stdin);
            d.scheduled[strcspn(d.scheduled, "\n")] = 0; // Remove newline character

            printf("Enter Updated Doctor Contact: ");
            fflush(stdin);
            fgets(d.contact, sizeof(d.contact), stdin);
            d.contact[strcspn(d.contact, "\n")] = 0; // Remove newline character

            fseek(fp, -sizeof(d), SEEK_CUR); // Move the file pointer back
            fwrite(&d, sizeof(d), 1, fp);
            break; // No need to continue looping
        }
    }
    fclose(fp);

    if (found == 0) {
        printf("Doctor with ID %d not found.\n", id);
    } else {
        printf("Doctor details updated successfully.\n");
    }
}
