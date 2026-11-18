# 1. Write a program to implement an address book with options given below: 
# a) Create address book. b) View address book. c)Insert a record. d) Delete a record. e) Modify a record. f) Exit.


file=""

check_file() {
    if [ -z "$file" ] || [ ! -f "$file" ]; then
        echo "Please create the address book first (option a)."
        return 1
    fi
    return 0
}

create_book() {
    read -p "Enter address book file name: " file
    > "$file"
    echo "Address book '$file' created."        
}

view_book() {
    check_file || return
    if [ ! -s "$file" ]; then
        echo "Address book is empty."
        return
    fi
    echo "ID : Name : Phone : Email"
    echo "-------------------------"
    cat "$file"
}

insert_record() {
    check_file || return
    read -p "Enter ID: " id
    if grep -q "^$id:" "$file"; then
        echo "A record with this ID already exists."
        return
    fi
    read -p "Enter name: " name
    read -p "Enter phone: " phone
    read -p "Enter email: " email
    echo "$id:$name:$phone:$email" >> "$file"
    echo "Record inserted."
}

delete_record() {
    check_file || return
    read -p "Enter ID to delete: " id
    if grep -q "^$id:" "$file"; then
        grep -v "^$id:" "$file" > temp.txt
        mv temp.txt "$file"
        echo "Record deleted."
    else
        echo "Record not found."
    fi
}

modify_record() {
    check_file || return
    read -p "Enter ID to modify: " id
    if grep -q "^$id:" "$file"; then
        read -p "Enter new name: " name
        read -p "Enter new phone: " phone
        read -p "Enter new email: " email
        grep -v "^$id:" "$file" > temp.txt
        echo "$id:$name:$phone:$email" >> temp.txt
        mv temp.txt "$file"
        echo "Record modified."
    else
        echo "Record not found."
    fi
}

while true; do
    echo ""
    echo "===== ADDRESS BOOK ====="
    echo "a) Create address book"
    echo "b) View address book"
    echo "c) Insert a record"
    echo "d) Delete a record"
    echo "e) Modify a record"
    echo "f) Exit"
    read -p "Enter your choice: " choice
    case $choice in
        a) create_book ;;
        b) view_book ;;
        c) insert_record ;;
        d) delete_record ;;
        e) modify_record ;;
        f) echo "Exiting..."; exit ;;
        *) echo "Invalid choice." ;;
    esac
done