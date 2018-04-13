function WithoutLast() {
  var string = prompt('Введите строку:');
  var lastChar = (string.slice(0, -1));
  alert( lastChar );
  return;
}
WithoutLast();