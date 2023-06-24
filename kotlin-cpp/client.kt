class HelloFromCpp(val from: String, val number: Int) {
 
    fun show() {
        println(bridge(from, number))
    }
 
    private external fun bridge(s: String, n: Int): String
 
    companion object {
            init {
                System.loadLibrary("cppfromkotlin")
            }
    }   
}
 
fun main(args: Array<String>) {
    val hello = HelloFromCpp("Hello from C++! ", 5)
    hello.show()
}
