function reverseString() {
    var string = prompt('Введите строку:');
    var newString = "";
    
    for (var i = string.length - 1; i >= 0; i--) {
        newString += string[i];
    }
    
    alert( newString );
    return;
}
reverseString();