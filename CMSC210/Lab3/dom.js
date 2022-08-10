function box1()
{
  var box = document.getElementById("box1");
  box.style.backgroundColor = "blue";
  box.style.color = "white";
}

function box2()
{
  var box = document.getElementById("box2");
  box.parentNode.removeChild(box);
}

function box3()
{
  var text = document.createTextNode("New Box");
  var newbox = document.createElement("div");
  newbox.appendChild(text);
  var box = document.getElementById("box3");
  box.parentNode.appendChild(newbox);
}

