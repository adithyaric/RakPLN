<?php include "koneksi.php"; ?>
<?php include "header.php"; ?>

<h1 class="text-center">Hapus Material</h1>
<hr>

<br>


<form enctype="multipart/form-data" method="POST" class="needs-validation" novalidate>
	<div class="container">
		<?php
		$id = $_GET['id'];
		$getBarang = $koneksi->query("SELECT * FROM tb_statistik WHERE id ='$id'");
		while ($ambil = $getBarang->fetch_assoc()) {
		?>
			<table class="table table-bordered table-hover">
				<tbody>
					<tr>
						<td width="150px">
							<input type="hidden" name="id" value="<?php echo $ambil['id']; ?>">
							Nama Material
						</td>
						<td>
							<input type="text" name="nama_barang" value="<?php echo $ambil['nama_barang']; ?>" readonly>
							<!-- <select name="nama_barang" class="form-control">
								<option value="<?php echo $ambil['nama_barang']; ?>"><?php echo $ambil['nama_barang']; ?></option>
							</select> -->
						</td>
					</tr>
				</tbody>
			</table>
		<?php } ?>
	</div>

	<br>

	<p style="text-align: center;">
		<button class="btn btn-primary mr-2" name="hapus_barang">Hapus</button>
		<a type="button" class="btn btn-danger mr-2" href="index.php">Batal</a>
	</p>

</form>

<style type="text/css">
	.table {
		margin: 0 auto;
		width: auto;
	}
</style>

<?php
if (isset($_POST['hapus_barang'])) {
	$id = $_POST['id'];
	$nama_barang = $_POST['nama_barang'];


	if (!empty($nama_barang) || !empty($jumlah_barang) || !empty($satuan_barang) || !empty($rak_baris) || !empty($rak_kolom)) {
		$koneksi->query("DELETE FROM tb_statistik WHERE id = '$id'");

		echo "<script>alert('Material berhasil dihapus !');</script>";
		echo "<script>location='index.php';</script>";
	} else {
		echo "<script>alert('Material gagal dihapus !');</script>";
	}
}

?>

<?php include "footer.php"; ?>