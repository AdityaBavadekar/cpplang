int i = 50
string s = "Heloo"

//  Samples to validate
|||
//Asignments
int i = 99
int i2 = 10 + 2000
string s1 = "This is a String"
string s2 = 'This is also a String'
bool b = false
bool checked = true

//Invalid Asignments
int i = 99&
int i2 = 10 $ 2000
int i2 = "10"
string s1 = 10
string s2 = -1
bool b = false + 40
bool checked = True

//Classes
class MyClassW() {}
class MyClassW() {return}
private class MyClass() > Hello {}
protected class MyClass1() > Hello, Hi {}
public class MyClassW() > Hello {}

//Invalid Classes
vip_access class MyClassW() {}
class MyClassW {return}
private class MyClass() > {}
protected class MyClass1() > Hello Hi {}
public class MyClassW() Hello {}

//Delete
delete i
delete i, s
//Invalid Delete
delete i s
delete i,
delete i, s,

//For loops
for i in 10{
    return s;
}

//Functions

fun add(int n1, int n2) > string {
    string s = "{n1 + n2}"
    return s;
}
fun addTwoNumbers() > string {
    string s = "Hello World" 
    return s;
}
|||