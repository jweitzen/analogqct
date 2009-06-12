use Win32::OLE;
#!/usr/local/bin/perl

($path)= ($0 =~ /(.*\\)/); #The variable $0 contains the full path and name of this perl script. $path extracts the path only
$TXT_temp_file_pathname=$path.'Temp.txt';

$QCAT_version = shift (@ARGV);


#----------------------------------------------------------------------------
# Start-up the QCAT Application
#----------------------------------------------------------------------------
my $qcat_app = new Win32::OLE "$QCAT_version.Application";

if(!$qcat_app)
{
   print "ERROR: Unable to invoke the QCAT application.\n";

   die;
}

my $filter = $qcat_app->{PacketFilter};

if(!$filter)
{
   print "ERROR: Unable to retrieve the Filter Object.\n";
   
   die;
}
$filter->SetAll(0);        #Disable all filters everything

$DLF_file_pathname = shift (@ARGV);

@Filter_codes = @ARGV;
	
foreach $Filter_code (@Filter_codes)
{
#	$Filter_code=$Filter_codes_list[$Filter_codes_index-1];
	$filter->Set($Filter_code, 1);
}

$filter->Commit();

$filter = NULL;
#----------------------------------------------------------------------------
# Process the Log File.
#----------------------------------------------------------------------------
my $ret_val = $qcat_app->Process($DLF_file_pathname, $TXT_temp_file_pathname, 0, 1);

if($ret_val==0)
{
   my $error_code = $qcat_app->{LastErrorCode};
   my $error_str  = $qcat_app->{LastError};

   print "Error: $error_str (Code=$error_code)\n";

   die;
}

#----------------------------------------------------------------------------
# Clean-up
#----------------------------------------------------------------------------
$qcat_app = NULL;
;

