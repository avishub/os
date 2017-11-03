#!/bin/bash

bookname=addressbook.txt
createAddressBook(){
	if test -e addressbook.txt
	then
		echo "Address book already created!"
	else
		touch addressbook.txt
		echo "Fname\t\tLname\t\tPhone No\t\t\tAddress" |  cat >> $bookname
		echo "-----------------------------------------------------------------------------------------------\n" |  cat >> addressbook.txt 
		echo "AddressBook Created"
	fi
}

viewAllAddressBook(){
 cat addressbook.txt
}

insertRecord(){
	ans=1
    while [ "$ans" -eq 1 ]
    do
	echo "Enter First Name: "
	read fname
	echo "Enter Last Name: "
	read lname
	echo "Enter Phone Number of $fname: "
	read contactno
	echo "Enter Address of $fname:"
	read address
	echo "$fname\t\t$lname\t\t$contactno\t\t\t$address" | cat >> $bookname 
	echo "Press 1 to insert more record!"
	read ans
	done

}
deleteRecord(){
	echo "Enter fname or phone no of record :"
	read pattern
	grep -n "$pattern" $bookname 
	returnstatus=`echo $?`

	if [ $returnstatus -eq 1 ]
	then
	    echo "No record found!"
	else	
		echo "Enter line number of record to be deleted"
		read linenumber

	    grep -n "$pattern" $bookname | while read line
		do
			number=`echo "$line" | cut -c1`
			if [ $number -eq $linenumber ]	
			then
				removerec="${linenumber}d"
				sed -i -e "$removerec" $bookname
				echo "Record Deleted"
			fi
		done
	fi	
}
modifyRecord(){
	echo "Enter fname or phone no of record :"
	read pattern
	grep -n "$pattern" $bookname 
	returnstatus=`echo $?`

	if [ $returnstatus -eq 1 ]
	then
	    echo "No record found!"
	else	
		echo "Enter line number of record to be modified"
		read linenumber
		echo "Enter First Name: "
		read fname
		echo "Enter Last Name: "
		read lname
		echo "Enter Phone Number of $fname: "
		read contactno
		echo "Enter Address of $fname:"
		read address
	    grep -n "$pattern" $bookname | while read line
		do
			number=`echo "$line" | cut -c1`
			if [ $number -eq $linenumber ]	
			then
				modifyrec="${linenumber}s"
				sed -i -e "$modifyrec/.*/$fname\t\t$lname\t\t$contactno\t\t\t$address/" $bookname
				echo "Record Updated"
			fi
		done
	fi	
}

viewAddressBook(){
	echo "Enter fname or phone no of record :"
	read pattern
	echo "Fname\t\tLname\t\tPhone No\t\t\tAddress\n"
	grep "$pattern" $bookname 
	returnstatus=`echo $?`	
	if [ $returnstatus -eq 1 ]
	then
	    echo "No record found!"
	fi	
}
while(true)
do
	echo "\n1. Create address book\n2. View All Addreass Book\n3. Insert new record\n4. Delete record\n5. Modify Record\n6. View Specific Record \n7. Exit\n>>"
	read ip
	case $ip in
		1) createAddressBook;;
		2) viewAllAddressBook;;
		3) insertRecord;;
		4) deleteRecord;;
		5) modifyRecord;;
		6) viewAddressBook;;
		7) exit;;
		*) echo "Invalid Choice!"
	esac		
done
