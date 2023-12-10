import express from 'express';
import of from 'os';
const NODE_PORT   = process.env["NODE_PORT"];

var counter = 0;

///////////////////////////////////////////////////////
//
// Server: Listen on NODE_PORT and serve the homepage
//


if (!NODE_PORT) {
	process.stderr.write("ERROR: missing NODE_PORT configuration variable\n");
	process.exitCode = 1;
} else {
	
	const app = express();
	app.get("/", getHomePage);
	process.stderr.write("listen on " + NODE_PORT + "\n")

	app.listen(NODE_PORT);
}


///////////////////////////////////////////////////////
//
// The only service available: 
//   - increment access counter
//   - inform about listening port and current count
//

function getHomePage(req, res) {
	const port = NODE_PORT;
	const counter = incrementAndGetCounter();
	
	const homePage = buildHomePage(port, counter);
	
	res.send(homePage);
}


///////////////////////////////////////////////////////
//
// Data access: 
//   - increment the access counter
//   - return the current count
//

function incrementAndGetCounter() {
	 counter = counter + 1;
	 return counter;
}

///////////////////////////////////////////////////////
//
// Build homepage: 
//   - title
//   - show listening port
//   - show counter, if available
//

function buildHomePage(port, counter, hostname) {
	return `
		<html>
			<body>
				<h1>TVS Application</h1>
				<p><strong>PORT: </strong>${port}</p>
				<hr>
				${
					counter ?
						`<p style="font-size: 1200%; font-family: sans-serif">${counter}</p>`
						:
						`<br><p style="color: red; font-style: italic">(database unavailable)</p>`
				 }
			</body>
		</html>
	`;
}
