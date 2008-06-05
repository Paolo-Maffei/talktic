package com.talktic;

import org.mozilla.javascript.*;
import java.io.*;
import java.util.Vector;

public class JSFile extends ScriptableObject {
	protected String name;
	protected File file;
	protected Vector<Character> bytes;
	protected int pos;
	protected boolean is_read, is_write;

	public JSFile() {
	}

	public static Scriptable jsConstructor
		(Context cx, Object[] args, Function ctorObj, boolean inNewExpr) {
		JSFile result = new JSFile();
		if(args.length > 0 && args[0] != Context.getUndefinedValue()) {
			result.name = Context.toString(args[0]);
			result.file = new File(result.name);
		}
		return result;
	}

	public String getClassName() {
		return "File";
	}

	public String jsGet_name() {
		return name;
	}

	public boolean jsFunction_open(String mode) throws IOException {
		jsFunction_close();
		if(file == null) {
			return false;
		}

		pos = 0;
		bytes = new Vector<Character>();

		if(mode.indexOf("r") != -1) {
			if(! file.exists()) {
				return false;
			}
			is_read = true;
			FileReader r = new FileReader(file);
			int b = -1;
			while((b = r.read()) != -1) {
				bytes.addElement((char)b);
			}
			r.close();
		}
		if(mode.indexOf("w") != -1) {
			is_write = true;
		}

		return true;
	}

	public boolean jsFunction_close() throws IOException {
		if(is_write) {
			FileWriter w = new FileWriter(file);
			for(int i=0; i<bytes.size(); i++) {
				char b = bytes.get(i);
				w.append(b);
			}
			w.flush();
			w.close();
		}
		return true;
	}

	public int jsFunction_readByte() throws IOException {
		if(pos < bytes.size()) {
			return bytes.get(pos++);
		} else {
			return -1;
		}
	}

	public String jsFunction_readln() throws IOException {
		String ret = new String();
		for(;pos<bytes.size();pos++) {
			char ch = bytes.get(pos);
			ret += ch;
			if(ch == '\n' || ch == '\n') {
				if(ch == '\r' && bytes.get(pos+1) == '\n') {
					pos++;
				}
				break;
			}
		}
		return ret;
	}
	
	public void jsFunction_setPosition(int p) throws IOException {
		pos = p;
	}

	public void jsFunction_ungetByte() throws IOException {
		pos--;
		if(pos<0) {
			pos = 0;
		}
	}

	public void jsFunction_write(String a) throws IOException {
		for(int i=0; i<a.length(); i++) {
			bytes.addElement(a.charAt(i));
		}
	}

	public void jsFunction_writeln(String a) throws IOException {
		jsFunction_write(a + "\n");
	}

	public void finalize() {
		try {
			jsFunction_close();
		} catch (IOException e) {
		}
	}

	private static JSFile checkInstance(Scriptable obj) {
		if (obj == null || !(obj instanceof JSFile)) {
			throw Context.reportRuntimeError("called on incompatible object");
		}
		return (JSFile) obj;
	}
}
