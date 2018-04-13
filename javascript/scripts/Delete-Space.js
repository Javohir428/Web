function DeleteSpaces() {
    var string = prompt('Введите строку:');
    var newString = string.replace(/\s+/g, ' ').trim();
    alert( newString );
    return;
}
DeleteSpaces();