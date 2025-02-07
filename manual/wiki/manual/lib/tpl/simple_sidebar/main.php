<?php
/**
	* DokuWiki Default Template
 *
 * This is the template you need to change for the overall look
 * of DokuWiki.
 *
 * You should leave the doctype at the very top - It should
 * always be the very first line of a document.
 *
 * @link   http://dokuwiki.org/templates
 * @author Andreas Gohr <andi@splitbrain.org>
 */

// must be run from within DokuWiki
if (!defined('DOKU_INC')) die();


    function _hide_email($email) {
          $encode = '';
          for ($x=0; $x < strlen($email); $x++) $encode .= '&#x' . bin2hex($email{$x}).';';
          return $encode;
    }

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php echo $conf['lang']?>"
 lang="<?php echo $conf['lang']?>" dir="<?php echo $lang['direction']?>">
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <title>
    <?php tpl_pagetitle()?>
    [<?php echo strip_tags($conf['title'])?>]
  </title>

 <?php
$bypass_sidebar = false;
$pages =tpl_getConf('sbar_closed');
if($pages) {
    global $ID;
    if(preg_match('/' . $ID .'/',$pages)) {
       $bypass_sidebar=true;
    }
}
 global $INPUT;
 $current_class = $INPUT->str('do');
if(($current_class && $current_class == 'admin')  || $bypass_sidebar) {
       echo  "<style type = 'text/css'>#toggler{ display: none; } </style>";
       $current_class="ssb_admin";
 }
 else {
     $current_class="ssb_std";
 }
 ?>

  <?php tpl_metaheaders()?>

  <link rel="shortcut icon" href="<?php echo DOKU_TPL?>images/favicon.ico" />

  <?php /*old includehook*/ @include(dirname(__FILE__).'/meta.html')?>
</head>

<body>
<?php /*old includehook*/ @include(dirname(__FILE__).'/topheader.html')?>

<!--  TOP BAR -->

<div id="top_bar" class="dokuwiki">

  <?php html_msgarea()?>

  <div class="stylehead">

    <div class="header">
      <div class="pagename">
        [[<?php tpl_link(wl($ID,'do=backlink'),tpl_pagetitle($ID,true),'title="'.$lang['btn_backlink'].'"')?>]]
      </div>
      <div class="logo">
        <?php tpl_link(wl(),$conf['title'],'name="dokuwiki__top" id="dokuwiki__top" accesskey="h" title="[H]"')?>
      </div>

      <div class="clearer"></div>
    </div>  <!-- header -->

    <?php /*old includehook*/ @include(dirname(__FILE__).'/header.html')?>

    <div class="bar" id="bar__top">
      <div class="bar-left" id="bar__topleft">
        <?php tpl_button('edit')?>
        <?php tpl_button('history')?>
      </div>

      <div class="bar-right" id="bar__topright">
        <?php tpl_button('recent')?>
        <?php tpl_searchform()?>&nbsp;
      </div>
      <div class="clearer"></div>
    </div>  <!-- bar__top -->
    <?php if($conf['breadcrumbs']){?>
    <div class="breadcrumbs">
      <?php tpl_breadcrumbs()?>
      <?php //tpl_youarehere() //(some people prefer this)?>
    </div>
    <?php }?>

    <?php if($conf['youarehere']){?>
    <div class="breadcrumbs">
      <?php tpl_youarehere() ?>
    </div>
    <?php }?>

  </div> <!-- stylehead -->

  <?php flush()?>

  <?php /*old includehook*/ @include(dirname(__FILE__).'/pageheader.html')?>
</div> <!--top_bar-->

<!--  TOP BAR END -->

<!--  WRAPPER START-->
<div id="wrapper">
<div id="main_page" class="dokuwiki">
<div id="toggler">
<a href="javascript:sbar_toggler.toggle();void 0"><img src="<?php echo DOKU_TPL?>images/toggle.png" title="toggle" border="0" /></a>
</div>
<div class="left_sidebar <?php echo $current_class;?>"  id="left_sidebar">
    
<?php 
	$ssbar = dirname(__FILE__).'/sidebar.html';	
	if(file_exists($ssbar)) {
	@include($ssbar);
	}
	else {
	  $ssbar = dirname(__FILE__).'/sidebar.php';
	  if(file_exists($ssbar)) {
	     @include($ssbar);
	  }
	 }
?>
<div id="personal_ssb">
<?php
 global $INFO;
$pageid = "sidebar:" . $INFO['client'];
tpl_include_page($pageid);
?>
</div>
</div>  <!-- end left_sidebar-->

  <div class="page">
 <div class="right_page <?php echo $current_class;?>"  id="right_page">

    <!-- wikipage start -->
    <?php tpl_content()?>
    <!-- wikipage stop -->
  </div>  <!-- right_page-->
  </div>  <!-- page -->


  <div class="clearer">&nbsp;</div>

  <?php flush()?>

 <div class="stylefoot  <?php echo $current_class;?>" id="bottom_div">

      
      <div class="meta">
        <?php tpl_userinfo()?>  <?php tpl_pageinfo()?>&nbsp;&nbsp;
      </div>
   
    

   <?php /*old includehook*/ @include(dirname(__FILE__).'/pagefooter.html')?>
   <br />
    <div class="bar  <?php echo $current_class;?>" id="bar__bottom">
      <div class="bar-left" id="bar__bottomleft">
        <?php tpl_button('edit')?>       
        <?php 
          global $updateVersion;
          if($updateVersion >= 35) {
             tpl_button('media');
          }
        ?>
        <?php tpl_button('subscribe')?>
        <?php tpl_button('admin')?>
        <?php tpl_button('profile')?>
        <?php tpl_button('login')?>
        <?php tpl_button('index')?>
        <?php tpl_button('top')?>&nbsp;
      </div>
      <div class="clearer"></div>
    </div>  <!-- end bar__bottom-->

  </div>  <!-- end stylefoot-->

</div>  <!-- end main_page -->

<div id="footer">
<?php /*old includehook*/ @include(dirname(__FILE__).'/footer.html') ?>
</div>


<div class="no"><?php /* provide DokuWiki housekeeping, required in all templates */ tpl_indexerWebBug()?></div>

</div>  <!-- wrapper -->
<!--  WRAPPER END -->
</body>
</html>
