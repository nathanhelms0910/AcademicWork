let messages = new Array();

function fetch_messages()
{
  $.get("/messages", function( data ) {
	  let new_messages = JSON.parse(data);

	  for(message in new_messages) {
	  	let obj = new_messages[message];
		let new_entry = { username: obj[0], topic: obj[1], text: obj[2]};
		let found = false;

		for(i = 0; i < messages.length; ++i) {
			if(messages[i].username == new_entry.username && messages[i].topic == new_entry.topic && messages[i].text == new_entry.text) {
				found = true;
			}
		}

		if(found == false) {
			code = '<span class=username>' + new_entry.username + '</span>:<br/>';
			code += '<span class=topic>' + new_entry.topic + '</span>:<br/>'
			code += '<p class=text>' + new_entry.text + '</p>'
			$("#messages").append(code);
			messages.push(new_entry);
		}
	}
});
}

function submit_form(event) {
  let message = $("#post_form").serialize();
  $.post("/add_message", message, function(data) {
	  if(data == "No message found") {
	  	console.log("No messages");
	  }
  });
  event.preventDefault();
  return true;
}

function submit_user(event) {
  let message = $("#user_form").serialize();
  $.post("/add_auth_user", message, function(data) {
	  if(data == "No user submitted") {
	  	console.log("No user given");
	  }
  });
  event.preventDefault();
  return true;
}

$(document).ready( function() {
	$("#post_form").submit(submit_form);
	$("#user_form").submit(submit_user);
	setInterval(fetch_messages, 500);
});
