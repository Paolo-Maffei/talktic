package com.talktic;

import org.mozilla.javascript.*;

import java.io.File;
import java.io.FileFilter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class JavaScriptCompiler {
	protected Context context;
	protected Scriptable global;

	public JavaScriptCompiler(String path) throws IOException {
		context = Context.enter();
		global = context.initStandardObjects();

		File files = new File(path);
		for(File f : files.listFiles(new FileFilter() {
			public boolean accept(File f) {
				return f.getName().endsWith(".js");
			}
		})) {
			try {
				context.evaluateReader(global, new FileReader(f), f.getPath(), 1, null);
			} catch(FileNotFoundException e) {
				System.err.println(e);
			}
		}
		try {
			ScriptableObject.defineClass(global, com.talktic.JSFile.class);
            ScriptableObject.putProperty(global, "stdout", Context.javaToJS(System.out, global));
            ScriptableObject.putProperty(global, "stderr", Context.javaToJS(System.err, global));
			context.evaluateString(global, "message = function(a) { stdout.println(a); }", "<str>", 1, null);
			context.evaluateString(global, "warning = function(a) { stderr.println; }", "<str>", 1, null);
			context.evaluateString(global, "error = function(a){ stderr.println(a); }", "<str>", 1, null);
			context.evaluateString(global, "File.byteToString = String.fromCharCode;", "<str>", 1, null);
		} catch(Exception e) {
			System.err.println(e);
		}
	}

	public void compile(String path) {
		Object result = context.evaluateString(global,
			"JSC$compile_file('"+path+"',JSC$FLAG_VERBOSE,'asm','bc');", "<str>",1,null);
		System.out.println(Context.toString(result));
	}

	public static void main(String[] args) {
		try {
			JavaScriptCompiler jsc = new JavaScriptCompiler(args[0]);
			jsc.compile(args[1]);
		} catch(Exception e) {
			System.err.println(e);
		}
	}
}
