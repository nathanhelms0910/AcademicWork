let i = 0;
function color()
{
  var colors = new Array();
  colors[0] = "#2f0034"
  colors[1] = "#800080" 
  colors[2] = "#33FAFF"
  colors[3] = "#2D4C4C"
  colors[4] = "#BD44B7"
  colors[5] = "#4464BD"
  document.bgColor= colors[i];
  alert("The value of i is: " + i);
  ++i;
  if(i >= 6) {
    i = 0;
  }
}


