.class public JoosApplet

.super java/applet/Applet

.field private protected returnPasswords Ljava/util/Vector;
.field private protected returnValues Ljava/util/Vector;

.method public <init>()V
  .limit locals 1
  .limit stack 4
  aload_0
  invokenonvirtual java/applet/Applet/<init>()V
  new java/util/Vector
  dup
  iconst_5
  iconst_1
  invokenonvirtual java/util/Vector/<init>(II)V
  dup
  aload_0
  swap
  putfield JoosApplet/returnPasswords Ljava/util/Vector;
  pop
  new java/util/Vector
  dup
  iconst_5
  iconst_1
  invokenonvirtual java/util/Vector/<init>(II)V
  dup
  aload_0
  swap
  putfield JoosApplet/returnValues Ljava/util/Vector;
  pop
  return
.end method

.method public addResult(Ljava/lang/String;Ljava/lang/String;)V
  .limit locals 3
  .limit stack 3
  aload_0
  getfield JoosApplet/returnPasswords Ljava/util/Vector;
  aload_0
  aload_1
  invokevirtual java/applet/Applet/getParameter(Ljava/lang/String;)Ljava/lang/String;
  invokevirtual java/util/Vector/addElement(Ljava/lang/Object;)V
  aload_0
  getfield JoosApplet/returnValues Ljava/util/Vector;
  aload_2
  invokevirtual java/util/Vector/addElement(Ljava/lang/Object;)V
  return
.end method

.method public returnResults()Z
  .limit locals 6
  .limit stack 5
  new joos/lib/JoosIO
  dup
  invokenonvirtual joos/lib/JoosIO/<init>()V
  dup
  astore_2
  pop
  new joos/lib/JoosURL
  dup
  aconst_null
  aload_0
  ldc "cgi-url"
  invokevirtual java/applet/Applet/getParameter(Ljava/lang/String;)Ljava/lang/String;
  invokenonvirtual joos/lib/JoosURL/<init>(Ljava/net/URL;Ljava/lang/String;)V
  dup
  astore_1
  pop
  aload_1
  invokevirtual joos/lib/JoosURL/openConnection()Z
  ifeq stop_0
  aload_1
  invokevirtual joos/lib/JoosURL/openOutputStream()Z
  ifeq stop_1
  aload_1
  new java/lang/Integer
  dup
  aload_0
  getfield JoosApplet/returnPasswords Ljava/util/Vector;
  invokevirtual java/util/Vector/size()I
  invokenonvirtual java/lang/Integer/<init>(I)V
  invokevirtual java/lang/Integer/toString()Ljava/lang/String;
  invokevirtual joos/lib/JoosURL/println(Ljava/lang/String;)Z
  pop
  iconst_0
  dup
  istore_3
  pop
  start_2:
  iload_3
  aload_0
  getfield JoosApplet/returnPasswords Ljava/util/Vector;
  invokevirtual java/util/Vector/size()I
  if_icmplt true_4
  iconst_0
  goto stop_5
  true_4:
  iconst_1
  stop_5:
  ifeq stop_3
  aload_0
  getfield JoosApplet/returnPasswords Ljava/util/Vector;
  iload_3
  invokevirtual java/util/Vector/elementAt(I)Ljava/lang/Object;
  checkcast java/lang/String
  dup
  astore 4
  pop
  aload_0
  getfield JoosApplet/returnValues Ljava/util/Vector;
  iload_3
  invokevirtual java/util/Vector/elementAt(I)Ljava/lang/Object;
  checkcast java/lang/String
  dup
  astore 5
  pop
  aload_1
  new java/lang/Integer
  dup
  aload 4
  invokevirtual java/lang/String/length()I
  invokenonvirtual java/lang/Integer/<init>(I)V
  invokevirtual java/lang/Integer/toString()Ljava/lang/String;
  invokevirtual joos/lib/JoosURL/println(Ljava/lang/String;)Z
  pop
  aload_1
  aload 4
  invokevirtual joos/lib/JoosURL/println(Ljava/lang/String;)Z
  pop
  aload_1
  new java/lang/Integer
  dup
  aload 5
  invokevirtual java/lang/String/length()I
  invokenonvirtual java/lang/Integer/<init>(I)V
  invokevirtual java/lang/Integer/toString()Ljava/lang/String;
  invokevirtual joos/lib/JoosURL/println(Ljava/lang/String;)Z
  pop
  aload_1
  aload 5
  invokevirtual joos/lib/JoosURL/println(Ljava/lang/String;)Z
  pop
  iload_3
  iconst_1
  iadd
  dup
  istore_3
  pop
  goto start_2
  stop_3:
  aload_1
  invokevirtual joos/lib/JoosURL/closeOutputStream()Z
  pop
  stop_1:
  stop_0:
  aload_1
  invokevirtual joos/lib/JoosURL/getErrorLog()Ljava/lang/String;
  aconst_null
  if_acmpne true_8
  iconst_0
  goto stop_9
  true_8:
  iconst_1
  stop_9:
  ifeq else_6
  aload_2
  ldc "***** Errors returning values from applet were: "
  invokevirtual joos/lib/JoosIO/println(Ljava/lang/String;)V
  aload_2
  aload_1
  invokevirtual joos/lib/JoosURL/getErrorLog()Ljava/lang/String;
  invokevirtual joos/lib/JoosIO/println(Ljava/lang/String;)V
  iconst_0
  ireturn
  goto stop_7
  else_6:
  iconst_1
  ireturn
  stop_7:
  nop
.end method

