var word="";
var picture = 0;
var wordbox = 0;
var guessed_letters = "";
var guesses = 0;
var svgns = "http://www.w3.org/2000/svg";

function draw_head()
{
  var head = document.createElementNS(svgns, "circle");
  head.setAttributeNS(null, "r", "30");
  head.setAttributeNS(null, "cx", "80");
  head.setAttributeNS(null, "cy", "80");
  head.setAttributeNS(null, "fill", "none");
  head.setAttributeNS(null, "stroke", "black");
  head.setAttributeNS(null, "stroke-width", "4px");
  picture.appendChild(head);
}

function draw_torso()
{
  var torso = document.createElementNS(svgns, "rect");
  torso.setAttributeNS(null, "width", "4px");
  torso.setAttributeNS(null, "height", "80px");
  torso.setAttributeNS(null, "x", "78");
  torso.setAttributeNS(null, "y", "110");
  torso.setAttributeNS(null, "fill", "black");
  picture.appendChild(torso);
}

function draw_arm(side)
{
  var arm = document.createElementNS(svgns, "line");
  arm.setAttributeNS(null, "stroke", "black");
  arm.setAttributeNS(null, "stroke-width", "2px");
  arm.setAttributeNS(null, "fill", "none");
  arm.setAttributeNS(null, "x1", "80");
  arm.setAttributeNS(null, "y1", "130");
  arm.setAttributeNS(null, "y2", "120");
  if(side == "left") {
    arm.setAttributeNS(null, "x2", "48");
  }
  else {
    arm.setAttributeNS(null, "x2", "108");
  }
  picture.appendChild(arm);

}

function draw_leg(side)
{
  var leg = document.createElementNS(svgns, "line");
  leg.setAttributeNS(null, "stroke", "black");
  leg.setAttributeNS(null, "stroke-width", "2px");
  leg.setAttributeNS(null, "fill", "none");
  leg.setAttributeNS(null, "x1", "80");
  leg.setAttributeNS(null, "y1", "180");
  leg.setAttributeNS(null, "y2", "170");
  if(side == "left") {
    leg.setAttributeNS(null, "x2", "48");
  }
  else {
    leg.setAttributeNS(null, "x2", "108");
  }
  picture.appendChild(leg);
}

function draw_eyes(side)
{
  var eyes = document.createElementNS(svgns, "circle");
  eyes.setAttributeNS(null, "r", "5");
  eyes.setAttributeNS(null, "fill", "black");
  eyes.setAttributeNS(null, "stroke", "black");
  eyes.setAttributeNS(null, "stroke-width", "4px");
  if(side == "left") {
    eyes.setAttributeNS(null, "cx", "65");
    eyes.setAttributeNS(null, "cy", "70");
  }
  else {
    eyes.setAttributeNS(null, "cx", "95");
    eyes.setAttributeNS(null, "cy", "70");
  }
  picture.appendChild(eyes);
}

function draw_nose()
{
  var nose = document.createElementNS(svgns, "rect");
  nose.setAttributeNS(null, "x", "78");
  nose.setAttributeNS(null, "y", "85");
  nose.setAttributeNS(null, "height", "5px");
  nose.setAttributeNS(null, "width", "2px");
  nose.setAttributeNS(null, "fill", "black");
  picture.appendChild(nose);
}

function draw_mouth()
{
  var mouth = document.createElementNS(svgns, "line");
  mouth.setAttributeNS(null, "x1", "74");
  mouth.setAttributeNS(null, "y1", "95");
  mouth.setAttributeNS(null, "x2", "82");
  mouth.setAttributeNS(null, "y2", "95");
  mouth.setAttributeNS(null, "stroke", "black");
  mouth.setAttributeNS(null, "stroke-width", "2px");
  mouth.setAttributeNS(null, "fill", "black");
  picture.appendChild(mouth);
}



function draw_next_body_part()
{
  if(guesses == 0)
  {
    draw_head();
  }
  else if(guesses == 1)
  {
    draw_torso();
  }
  else if(guesses == 2)
  {
    draw_arm("left");
  }
  else if(guesses == 3)
  {
    draw_arm("right");
  }
  else if(guesses == 4)
  {
    draw_leg("left");
  }
  else if(guesses == 5)
  {
    draw_leg("right");
  }
  else if(guesses == 6)
  {
    draw_eyes("left");
  }
  else if(guesses == 7)
  {
    draw_eyes("right");
  }
  else if(guesses == 8)
  {
    draw_nose();
  }
  else if(guesses == 9)
  {
    draw_mouth();
  }

}

function check_win()
{
  if(guesses > 10)
    return false;
  for(i = 0; i < word.length; ++i) {
    if(guessed_letters.includes(word[i]) == false)
      return false;
  }
  return true;
}

function draw_letter(i) {
  var letter = word[i];
  var letterNode = document.createTextNode(letter);
  var letterBox = document.createElement("div");
  letterBox.appendChild(letterNode);
  letterBox.setAttribute("class", "guessedletter");

  x = 20 + 80*i - word.length*80;
  letterBox.style.transform = "translate(" + x + "px, -40px)";
  wordbox.appendChild(letterBox);
}

function update_guessed_letters(letter)
{
  guessed_letters += letter;

  var letNode = document.createTextNode(letter + " ");
  var guess_box = document.getElementById("letters");
  guess_box.appendChild(letNode);
}

function draw_word()
{
  for (i=0; i < word.length; ++i) {
    var image = document.createElement("img");
    image.src = "Tile.png";
    wordbox.appendChild(image);
  }
}

  function handle_guess(event)
  {
    var letter = String.fromCharCode(event.which);
    if(guessed_letters.includes(letter))
      return;

    update_guessed_letters(letter);
    var found = false;
    for(i=0; i < word.length; ++i) {
      if(letter == word[i]) {
	found = true;
	draw_letter(i);
      }
    }
    if(found != true) {
      if(guesses >= 10) {
	alert("You're hung! Reload to play again.")
      }
      else {
	draw_next_body_part();
	++guesses;
      }
    }
    if(check_win()) {
      alert("Congratulation! You win!");
    }
  }

  function load_game()
  {
    word = prompt("Please enter a word for the game (all lowercase)", "word");
    picture = document.getElementById("gallows");
    wordbox = document.getElementById("contents");
    draw_word();
    document.body.addEventListener("keypress", handle_guess);
    
  }



