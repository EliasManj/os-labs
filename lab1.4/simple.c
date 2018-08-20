#include <linux/init.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/utsname.h>

#define SIZE 10

struct Student {
	int ID;
	char name[50];
	int age;
};

// Custom functions.
void uptime(void);
void getSystemInfo(void);
void StudentsMain(void);
void Add(struct Student student);
void List(struct Student students[SIZE]);
void strcopy(volatile char *dest, volatile char *source);

void strcopy(volatile char *dest, volatile char *source) {
	char data;
	do {
		data = *dest++ = *source++;
	} while (data);
}

struct Student students[SIZE];
int s_index = 0;

void Add(struct Student student){
	students[s_index] = student;
	s_index++;
}

void List(struct Student students[SIZE]){
	int i;
	for(i=0;i<s_index;i++){
		printk("Name: %s, age: %d", students[i].name, students[i].age);
	}
}

void StudentsMain(){
	struct Student student0;
	struct Student student1;
	student0.ID = 0;
	strcopy(student0.name, "Juan");
	student0.age = 20;
	student1.ID = 1;
	strcopy(student1.name, "Raymond");
	student1.age = 30;
	Add(student0);
	Add(student1);
	List(students);
}

// This function is called when the module is loaded.
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
	StudentsMain();
       uptime();
       getSystemInfo();
       return 0;
}

// This function is called when the module is removed.
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
}


// This functions gets the uptime
void uptime() {
  printk("Uptime: %i\n", jiffies_to_msecs(get_jiffies_64())/1000);
}


// This function gets the general system information
void getSystemInfo(){  
  struct new_utsname *buf;
  buf = utsname();

  printk("Nodename: %s\n",buf->nodename);
  printk("Machine: %s\n",buf->machine);
  printk("Sysname: %s\n",buf->sysname);
  printk("Release: %s\n",buf->release);
  printk("Version: %s\n",buf->version);
#ifdef __linux__
  printk("Domain Name: %s\n", buf->domainname); // GNU extension
#endif
}


/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
