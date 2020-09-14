const fs = require('fs');
const cp = require('child_process');

// library arguments for linking
var libraries = [''];

// if we want to build for debug or release
var debug = true;

var exec = '';

if(process.platform == 'linux' || process.platform == 'darwin') {
    exec = 'main'
} else if(process.platform == 'win32' ) {
    exec = 'main.exe'
}

// read the src directory for files
fs.readdir('./src', (err, f) => {
    if (err) {
        console.err("ERROR:", err);
        process.exit(0);
    } else {
        // exclude main because we are building object files
        let files = f.filter(x => !x.includes('main'));

        files.forEach((v) => {
            let oName = v.replace('.c', '.o');
            try {
                fs.unlinkSync(`lib/${oName}`);
            } catch (error) {
                console.error(error);
            }
            // this is for -g flag which tells compiler to include debug symbols
            let g = debug ? '-g' : '';
            let lib = "";
            // fill lib variable with library arguments
            libraries.forEach((v) => lib = lib + " " + v);
            // ${g} ${v} -o ${oName} ${lib}
            cp.execSync(`gcc ${g} src/${v} -o lib/${oName} ${lib} -c`, (err, stdout, stderr) => {
                if (err) {
                    console.error(err);
                    console.error(stderr);
                    process.exit(0);
                } else {
                    console.log(stdout);
                    console.log("Command Executed Successfully", oName);
                }
            });
        });

        let fileNames = "";
        let g = debug ? '-g' : '';
        files.forEach((v) => fileNames = fileNames + " " + "lib/" + v.replace('.c', '.o'));
        let lib = "";
        libraries.forEach((v) => lib = lib + " " + v);
        console.log(fileNames);
        cp.exec(`gcc ${g} src/main.c -o build/${exec} ${fileNames} ${lib}`, (err, stdout, stderr) => {
            if (err) {
                console.error(err);
                console.error(stderr);
                process.exit(0);
            } else {
                console.log(stdout);
                console.log(`Command Executed Successfully ${exec}`);
            }
        })
    }
})
